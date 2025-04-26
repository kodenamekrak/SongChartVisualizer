#include "main.hpp"
#include "UI/ChartView.hpp"
#include "ModConfig.hpp"
#include "Services/SvcAssetLoader.hpp"

#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"

#include "Tweening/FloatTween.hpp"

#include "bsml/shared/Helpers/creation.hpp"

#include "HMUI/ImageView.hpp"

#include "UnityEngine/Canvas.hpp"
#include "UnityEngine/RenderMode.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"

#include "System/Action_1.hpp"
#include "System/Collections/Generic/LinkedListNode_1.hpp"
#include "System/Collections/Generic/LinkedList_1.hpp"

#include "custom-types/shared/delegate.hpp"

#include "HMUI/CurvedCanvasSettings.hpp"

DEFINE_TYPE(SongChartVisualizer, ChartView);

using namespace UnityEngine;
using namespace GlobalNamespace;

namespace SongChartVisualizer
{

    void ChartView::ctor(AudioTimeSyncController *audioTimeSyncController, IReadonlyBeatmapData *readonlyBeatmapData, GlobalNamespace::BeatmapKey beatmapKey, Tweening::TimeTweeningManager *timeTweeningManager)
    {
        _audioTimeSyncController = audioTimeSyncController;
        _beatmapData = readonlyBeatmapData;
        _beatmapKey = beatmapKey;
        _timeTweeningManager = timeTweeningManager;

        INVOKE_CTOR();
    }

    void ChartView::Initialize()
    {
        INFO("Initializing graph");

        bool is360Level = _beatmapKey.beatmapCharacteristic->requires360Movement;
        Vector3 pos = is360Level ? getModConfig().nonStandardLevelPosition.GetValue() : getModConfig().standardLevelPosition.GetValue();
        Quaternion rot = Quaternion::Euler(is360Level ? getModConfig().nonStandardLevelRotation.GetValue() : getModConfig().standardLevelRotation.GetValue());
        auto chartSize = UnityEngine::Vector2(getModConfig().showNpsLines.GetValue() ? 108 : 105, 65);
        _floatingScreen = BSML::FloatingScreen::CreateFloatingScreen(chartSize, false, pos, rot, 0, getModConfig().showBackground.GetValue());
        _floatingScreen->GetComponent<Canvas*>()->set_sortingOrder(0);

        _comboUIController = UnityEngine::Resources::FindObjectsOfTypeAll<ComboUIController*>().front_or_default();
        _floatingScreen->get_transform()->SetParent(_comboUIController->get_transform()->parent, true);

        if (getModConfig().showBackground.GetValue())
        {
            DEBUG("Setting background");
            auto image = _floatingScreen->GetComponent<Canvas *>()->get_transform()->GetComponentsInChildren<HMUI::ImageView *>().front_or_default([](auto x)
                                                                                                                                                 { return x->get_name() == "bg"; });
            auto color = getModConfig().backgroundColor.GetValue();
            color.a = getModConfig().backgroundOpacity.GetValue();
            image->set_color(color);
            image->set_material(NoGlowMaterial);
        }

        if (_audioTimeSyncController->get_songLength() < 0)
        {
            _shouldNotRunTick = true;
            return;
        }

        _npsSections = GetNpsSections(_beatmapData);
        if (_npsSections.size() <= 0)
        {
            DEBUG("_npsSections was empty, destroying graph");
            UnityEngine::Object::Destroy(_floatingScreen);
            _shouldNotRunTick = true;
            return;
        }

        _windowGraph = _floatingScreen->get_gameObject()->AddComponent<WindowGraph *>();
        _windowGraph->_canvas = _floatingScreen->GetComponent<Canvas *>();

        std::vector<float> values;
        for (int i = 0; i < _npsSections.size(); i++)
            values.push_back(_npsSections[i].Nps);

        _currentSectionIdx = 0;
        _currentSection = _npsSections[_currentSectionIdx];

        _windowGraph->ShowGraph(values, getModConfig().lineColor.GetValue());
        _selfCursor = CreateSelfCursor(getModConfig().pointerColor.GetValue());

        if (getModConfig().peakWarning.GetValue())
        {
            auto iter = std::max_element(std::begin(values), std::end(values));
            _hardestSectionIdx = iter - values.begin();
            INFO("Peak warning is at index {}", _hardestSectionIdx);

            PrepareWarningText();
            FadeInTextIfNeeded();
        }
    }

    void ChartView::Tick()
    {
        if (_shouldNotRunTick)
            return;

        if (_audioTimeSyncController->songTime > _currentSection.ToTime)
        {
            _currentSectionIdx++;
            if (_currentSectionIdx + 1 >= _npsSections.size())
            {
                _shouldNotRunTick = true;
                return;
            }

            if (getModConfig().peakWarning.GetValue())
                FadeInTextIfNeeded();

            _currentSection = _npsSections[_currentSectionIdx];
        }

        auto dotpos = Vector3::Lerp(_windowGraph->dotObjects[_currentSectionIdx]->GetComponent<RectTransform *>()->get_position(),
                                    _windowGraph->dotObjects[_currentSectionIdx + 1]->GetComponent<RectTransform *>()->get_position(),
                                    (_audioTimeSyncController->songTime - _currentSection.FromTime) / (_currentSection.ToTime - _currentSection.FromTime));
        dotpos.z -= 0.001f;
        _selfCursor->get_transform()->set_position(dotpos);

        if (getModConfig().peakWarning.GetValue() && _peakWarningGo->get_activeSelf())
        {
            float timeTillPeakLocal = _currentSection.ToTime - _audioTimeSyncController->songTime;
            if (_timeTillPeak - timeTillPeakLocal < 0.05f)
                return;

            _timeTillPeak = timeTillPeakLocal;
            _peakWarningText->text = fmt::format("You're about to reach the peak difficulty in <color=#ffa500ff>{:.1f}</color> seconds!", _timeTillPeak);
        }
    }

    GameObject *ChartView::CreateSelfCursor(UnityEngine::Color color)
    {
        GameObject* selfCursor = GameObject::New_ctor("SelfCursor");
        selfCursor->get_transform()->SetParent(_floatingScreen->GetComponent<Canvas*>()->transform, false);

        auto image = selfCursor->AddComponent<HMUI::ImageView *>();
        image->set_color(color);
        image->set_material(NoGlowMaterial);

        auto rect = selfCursor->GetComponent<RectTransform *>();
        rect->set_sizeDelta(Vector2(1.2f, 1.2f));
        return selfCursor;
    }

    std::vector<NpsInfo> ChartView::GetNpsSections(IReadonlyBeatmapData *beatmapData)
    {
        std::vector<NpsInfo> npsSections;

        float songDuration = _audioTimeSyncController->get_songLength();
        if (songDuration < 0)
            return npsSections;

        // beatmapData->GetBeatmapDataItems crashes 
        std::vector<NoteData*> notes;
        for(auto node = beatmapData->allBeatmapDataItems->head; node != nullptr; node = node->Next)
        {
            if(node->Value->type != BeatmapDataItem::BeatmapDataItemType::BeatmapObject || node->Value->subtypeGroupIdentifier != 0)
                continue;
            
            if(auto noteData = il2cpp_utils::try_cast<NoteData>(node->Value))
            {
                if(noteData.value()->gameplayType != NoteData::GameplayType::Bomb)
                    notes.push_back(noteData.value());
            }
        }
        DEBUG("Got {} NoteData items", notes.size());

        if(notes.empty())
            return npsSections;

        std::sort(notes.begin(), notes.end(), [](NoteData *a, NoteData *b)
                  { return a->time < b->time; });

        int tempNoteCount = 0;
        float startingTime = notes[0]->time;
        npsSections.push_back(NpsInfo(0, 0, startingTime));

        for (int i = 0; i < notes.size(); ++i)
        {
            tempNoteCount++;
            if (i <= 0 || (i % 25 != 0 && i + 1 != notes.size()))
                continue;

            float nps;
            if (tempNoteCount >= 25)
                nps = tempNoteCount / (notes[i]->time - startingTime);
            else
                nps = notes.size() < 25 ? tempNoteCount / (notes[i]->time - notes[0]->time) : 25 / (notes[i]->time - notes[i - 25]->time);

            if (!isinf(nps))
                npsSections.push_back(NpsInfo(nps, startingTime, notes[i]->time));

            tempNoteCount = 0;
            startingTime = notes[i]->time;
        }

        npsSections.push_back(NpsInfo(0, startingTime, songDuration));
        return npsSections;
    }

    void ChartView::PrepareWarningText()
    {
        _peakWarningGo = GameObject::New_ctor("DiffWarningCanvas");
        auto canvas = _peakWarningGo->AddComponent<Canvas *>();
        canvas->set_renderMode(RenderMode::WorldSpace);

        _peakWarningGo->AddComponent<HMUI::CurvedCanvasSettings *>()->SetRadius(0);

        auto canvasTransform = canvas->get_transform();
        canvasTransform->set_position(Vector3(0, 2.25f, 3.5f));
        canvasTransform->set_localScale(Vector3::op_Division(canvasTransform->localScale, 100));

        if (RectTransform* rect = canvasTransform.try_cast<RectTransform>().value_or(nullptr))
        {
            rect->set_sizeDelta(Vector2(140, 50));

            _peakWarningText = BSML::Helpers::CreateText(rect, "", Vector2::get_zero());
            _peakWarningText->set_alignment(TMPro::TextAlignmentOptions::Center);
            _peakWarningText->set_fontSize(16);
            _peakWarningText->set_alpha(0);
        }

        _peakWarningGo->SetActive(false);

        _timeTillPeak = _audioTimeSyncController->get_songLength();
    }

    void ChartView::FadeInTextIfNeeded()
    {
        bool oldState = _peakWarningGo->get_activeSelf();
        bool newState = _currentSectionIdx + 1 == _hardestSectionIdx;
        if (oldState == newState)
            return;

        _peakWarningGo->SetActive(newState);
        if (!oldState && newState)
            FadeInText(_peakWarningText, (_currentSection.ToTime - _audioTimeSyncController->songTime) * 0.2f);
    }

    void ChartView::FadeInText(HMUI::CurvedTextMeshPro *text, float t)
    {
        INFO("Fading in peak warning text");
        auto delegate = custom_types::MakeDelegate<System::Action_1<float> *>(std::function([text](float value)
        {
            text->set_alpha(value);
        }));
        _timeTweeningManager->AddTween(Tweening::FloatTween::New_ctor(0, 1, delegate, t, EaseType::Linear, 0), this, false);
    }
}
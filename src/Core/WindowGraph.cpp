#include "main.hpp"
#include "Core/WindowGraph.hpp"
#include "Services/SvcAssetLoader.hpp"

#include "HMUI/ImageView.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/GameObject.hpp"

#include "bsml/shared/Helpers/creation.hpp"

DEFINE_TYPE(SongChartVisualizer, WindowGraph);

using namespace UnityEngine;

namespace SongChartVisualizer
{

	void WindowGraph::ShowGraph(std::vector<float> valueList, Color linkColor)
	{
		getLogger().info("Showing graph");

		Vector2 graphSizeDelta = Vector2(105, 65);
		float width = graphSizeDelta.x;
		float height = graphSizeDelta.y;

		float yMaximum = valueList[0];
		float yMinimum = valueList[0];

		for (int i = 0; i < valueList.size(); i++)
		{
			auto value = valueList[i];
			if (value > yMaximum)
				yMaximum = value;

			if (value < yMinimum)
				yMinimum = value;
		}

		auto yDifference = yMaximum - yMinimum;
		if (yDifference <= 0)
			yDifference = 5;

		yMaximum += yDifference * 0.2f;
		yMinimum -= yDifference * 0.2f;

		float xSize = width / (valueList.size() + 1);

		GameObject *lastCircleGameObject = nullptr;
		for (int i = 0; i < valueList.size(); i++)
		{
			auto xPosition = xSize + i * xSize;
			auto yPosition = (valueList[i] - yMinimum) / (yMaximum - yMinimum) * height;
			auto circleGameObject = CreateCircle(Vector2(xPosition, yPosition), false);
			dotObjects.push_back(circleGameObject);

			if (lastCircleGameObject)
			{
				linkPositions.push_back(CreateDotConnection(lastCircleGameObject->GetComponent<RectTransform *>()->get_anchoredPosition(),
															Vector2(xPosition, yPosition),
															linkColor));
			}

			lastCircleGameObject = circleGameObject;
		}

		auto maxNps = *std::max_element(valueList.begin(), valueList.end());
		auto minNps = *std::min_element(valueList.begin(), valueList.end());
		auto maxPoint = (maxNps - yMinimum) / (yMaximum - yMinimum) * height;
		auto minPoint = (minNps - yMinimum) / (yMaximum - yMinimum) * height;
		CreateNpsLines(std::make_pair(maxNps, maxPoint), std::make_pair(minNps, minPoint));
	}

	GameObject *WindowGraph::CreateDotConnection(Vector2 dotPositionA, Vector2 dotPositionB, Color linkColor)
	{
		GameObject *go = GameObject::New_ctor("DotConnection");
		go->get_transform()->SetParent(_canvas->get_transform(), false);

		auto image = go->AddComponent<HMUI::ImageView *>();
		image->set_color(linkColor);
		image->set_material(get_noGlowMaterial());

		auto dir = (dotPositionB - dotPositionA).get_normalized();
		auto distance = Vector2::Distance(dotPositionA, dotPositionB);

		auto rect = go->GetComponent<RectTransform *>();
		rect->set_anchorMin(Vector2(0, 0));
		rect->set_anchorMax(Vector2(0, 0));
		rect->set_sizeDelta(Vector2(distance, 0.2f));
		rect->set_anchoredPosition(UnityEngine::Vector2(dotPositionA + dir * distance * 0.5f));
		rect->set_localEulerAngles(Vector3(0, 0, atan2(dir.y, dir.x) * 57.29578f));

		return go;
	}

	void WindowGraph::CreateNpsLines(std::pair<float, float> maxPoints, std::pair<float, float> minPoints)
	{
		float npsDifference = maxPoints.first - minPoints.first;
		float posDifference = maxPoints.second - minPoints.second;
		float oneNpsGraphLength = posDifference / npsDifference;
		int npsIncrement = (int)(npsDifference / 10.0f) + 1;
		float zeroNpsPoint = minPoints.second - (minPoints.first * oneNpsGraphLength);

		int currentNps = -npsIncrement;

		while(currentNps < maxPoints.first){
			currentNps += npsIncrement;
			GameObject *go = GameObject::New_ctor("NpsLine");
			go->get_transform()->SetParent(_canvas->get_transform(), false);

			auto image = go->AddComponent<HMUI::ImageView *>();
			image->set_color(UnityEngine::Color::get_gray());
			image->set_material(get_noGlowMaterial());

			auto currentPosition = zeroNpsPoint + ((float)currentNps * oneNpsGraphLength);

			auto npsText = BSML::Helpers::CreateText<TMPro::TextMeshProUGUI*>(go->get_transform(), std::to_string(currentNps), {-50, 0}, {1, 1});
			npsText->set_fontSize(3);
			npsText->set_color(Color::get_gray());
			npsText->set_alignment(TMPro::TextAlignmentOptions::Center);

			auto rect = go->GetComponent<RectTransform *>();
			rect->set_anchorMin(Vector2(0, 0));
			rect->set_anchorMax(Vector2(0, 0));
			rect->set_sizeDelta(Vector2(105, 0.2f));
			rect->set_anchoredPosition(Vector2(52.5, currentPosition));
			rect->set_localEulerAngles(Vector3(0, 0, 0));
		}
	}

	GameObject *WindowGraph::CreateCircle(Vector2 anchoredPosition, bool makeDotsVisible)
	{
		GameObject *go = GameObject::New_ctor("Circle");
		go->get_transform()->SetParent(_canvas->get_transform(), false);

		auto image = go->AddComponent<HMUI::ImageView *>();
		image->set_material(get_noGlowMaterial());
		image->set_enabled(makeDotsVisible);
		image->set_sprite(get_circleSprite());

		auto rect = go->GetComponent<RectTransform *>();
		rect->set_anchoredPosition(anchoredPosition);
		rect->set_sizeDelta(Vector2(0.7f, 0.7f));
		rect->set_anchorMin(Vector2(0, 0));
		rect->set_anchorMax(Vector2(0, 0));

		return go;
	}
}
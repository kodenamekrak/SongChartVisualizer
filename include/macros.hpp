#define DECLARE_VECTOR_INCREMENT(name) \
DECLARE_INSTANCE_FIELD(BSML::IncrementSetting*, name##XIncrement); \
DECLARE_BSML_PROPERTY(float, name##XValue); \
DECLARE_INSTANCE_FIELD(BSML::IncrementSetting*, name##YIncrement); \
DECLARE_BSML_PROPERTY(float, name##YValue); \
DECLARE_INSTANCE_FIELD(BSML::IncrementSetting*, name##ZIncrement); \
DECLARE_BSML_PROPERTY(float, name##ZValue);

#define DEFINE_VECTOR_INCREMENT(name, configValue) \
float SettingsViewController::get_##name##XValue(){ return getModConfig().configValue.GetValue().x; } \
void SettingsViewController::set_##name##XValue(float value) { auto vec = getModConfig().configValue.GetValue(); vec.x = value; getModConfig().configValue.SetValue(vec); } \
float SettingsViewController::get_##name##YValue(){ return getModConfig().configValue.GetValue().y; } \
void SettingsViewController::set_##name##YValue(float value) { auto vec = getModConfig().configValue.GetValue(); vec.y = value; getModConfig().configValue.SetValue(vec); } \
float SettingsViewController::get_##name##ZValue(){ return getModConfig().configValue.GetValue().z; } \
void SettingsViewController::set_##name##ZValue(float value) { auto vec = getModConfig().configValue.GetValue(); vec.z = value; getModConfig().configValue.SetValue(vec); }

#define DEFINE_BSML_PROPERTY(type, name) \
type SettingsViewController::get_##name() { return getModConfig().name.GetValue(); } \
void SettingsViewController::set_##name(type value) { getModConfig().name.SetValue(value); }
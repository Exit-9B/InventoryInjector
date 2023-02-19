#include "RuleParser.h"

#include "Data/Defines/Actor.h"
#include "Data/Defines/Ammo.h"
#include "Data/Defines/Armor.h"
#include "Data/Defines/Book.h"
#include "Data/Defines/Form.h"
#include "Data/Defines/Magic.h"
#include "Data/Defines/Misc.h"
#include "Data/Defines/Potion.h"
#include "Data/Defines/SoulGem.h"
#include "Data/Defines/Weapon.h"

namespace Data
{
	Rule RuleParser::ParseRule(const Json::Value& a_rule)
	{
		Rule parsed{};

		const Json::Value& match = a_rule["match"];
		const Json::Value& assign = a_rule["assign"];

		if (!match.isObject() || !assign.isObject()) {
			return parsed;
		}

		RE::FormType formType = RE::FormType::None;
		util::try_get(FormTypeMap, match["formType"].asString(), formType);

		for (auto& name : match.getMemberNames()) {
			if (name.empty() || name[0] == '$') {
				continue;
			}

			const Json::Value& prop = match[name];

			if (const auto parser = GetPropertyParser(name, formType)) {
				parser->Parse(prop, &parsed);
			}
		}

		for (auto& name : assign.getMemberNames()) {
			if (name.empty() || name[0] == '$') {
				continue;
			}

			const Json::Value& val = assign[name];

			if (const auto parser = GetCustomDataParser(name, formType)) {
				parser->Parse(val, &parsed);
			}
		}

		return parsed;
	}

	using MakePropertyParser_t = std::shared_ptr<PropertyParser>(const std::string&, RE::FormType);

	template <typename T>
	std::shared_ptr<PropertyParser> MakePropertyParser(const std::string& a_name, RE::FormType)
	{
		return std::make_shared<T>(a_name);
	}

	const std::map<std::string, MakePropertyParser_t*> PropertyParserMap = {
		{ "formType", MakePropertyParser<FormTypeParser> },
		{ "formId", MakePropertyParser<FormIDParser> },
		{ "keywords", MakePropertyParser<KeywordsParser> },
		{ "mainPart", MakePropertyParser<MainPartParser> },
		{ "parts", MakePropertyParser<PartsParser> },
		{ "weightClass", MakePropertyParser<EnumParser<WeightClass>> },
		{ "weaponType", MakePropertyParser<EnumParser<RE::WEAPON_TYPE>> },
		{ "equipSlot", MakePropertyParser<FormIDParser> },
		{ "gemSize", MakePropertyParser<EnumParser<SoulGemType>> },
		{ "status", MakePropertyParser<EnumParser<SoulGemStatus>> },
		{ "bookType", MakePropertyParser<EnumParser<RE::OBJ_BOOK::Type>> },
		{ "teachesSkill", MakePropertyParser<EnumParser<RE::ActorValue>> },
		{ "teachesSpell", MakePropertyParser<FormIDParser> },
		// SkyUI replaces actorValue with primaryValue
		{ "primaryValue", MakePropertyParser<EnumParser<RE::ActorValue>> },
		// SkyUI replaces magicType with resistance
		{ "resistance", MakePropertyParser<EnumParser<RE::ActorValue>> },
		{ "school", MakePropertyParser<EnumParser<RE::ActorValue>> },
		{ "spellType", MakePropertyParser<EnumParser<SpellType>> },
		{ "archetype", MakePropertyParser<EnumParser<EffectArchetype>> },
		{ "deliveryType", MakePropertyParser<EnumParser<Delivery>> },
		{ "castType", MakePropertyParser<EnumParser<CastingType>> },
		{ "effectFlags", MakePropertyParser<BitfieldParser<EffectFlag>> },
		{ "iconColor", MakePropertyParser<ColorParser> },
		// clang-format off
		{ "flags",
			+[](const std::string& a_name,
				RE::FormType a_formType) -> std::shared_ptr<PropertyParser>
			{
				switch (a_formType) {
				case RE::FormType::Book:
					return std::make_shared<BitfieldParser<BookFlag>>(a_name);
				case RE::FormType::Ammo:
					return std::make_shared<BitfieldParser<AmmoFlag>>(a_name);
				case RE::FormType::AlchemyItem:
					return std::make_shared<BitfieldParser<PotionFlag>>(a_name);
				default:
					return std::make_shared<PropertyParser>(a_name);
				}
			}
		},
		{ "subType",
			+[](const std::string& a_name,
				RE::FormType a_formType) -> std::shared_ptr<PropertyParser>
			{
				switch (a_formType) {
				case RE::FormType::Armor:
					return std::make_shared<EnumParser<EquipType>>(a_name);
				case RE::FormType::Book:
					return std::make_shared<EnumParser<BookType>>(a_name);
				case RE::FormType::Misc:
					return std::make_shared<EnumParser<MiscType>>(a_name);
				case RE::FormType::Weapon:
					return std::make_shared<EnumParser<WeaponType>>(a_name);
				case RE::FormType::Ammo:
					return std::make_shared<EnumParser<AmmoType>>(a_name);
				case RE::FormType::AlchemyItem:
					return std::make_shared<EnumParser<PotionType>>(a_name);
				case RE::FormType::SoulGem:
					return std::make_shared<EnumParser<SoulGemType>>(a_name);
				default:
					return std::make_shared<PropertyParser>(a_name);
				}
			}
		},
		// clang-format on
	};

	std::shared_ptr<PropertyParser> RuleParser::GetPropertyParser(
		const std::string& a_name,
		RE::FormType a_formType)
	{
		if (auto it = PropertyParserMap.find(a_name); it != PropertyParserMap.end()) {
			return it->second(a_name, a_formType);
		}

		return std::make_shared<PropertyParser>(a_name);
	}

	std::shared_ptr<CustomDataParser> RuleParser::GetCustomDataParser(
		const std::string& a_name,
		RE::FormType a_formType)
	{
		if (a_name == "iconColor") {
			return std::make_shared<IconColorParser>(a_name);
		}
		else if (a_name == "subType") {
			return std::make_shared<SubTypeParser>(a_name, a_formType);
		}
		else if (a_name == "weightClass") {
			return std::make_shared<WeightClassParser>(a_name);
		}
		else {
			return std::make_shared<CustomDataParser>(a_name);
		}
	}
}

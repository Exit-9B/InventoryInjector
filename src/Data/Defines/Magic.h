#pragma once

namespace Data
{
	template <typename Enum>
	extern const util::enum_dict<Enum> EnumLookup;

	using RE::MagicSystem::SpellType;

	template <>
	inline const util::enum_dict<SpellType> EnumLookup<SpellType> = {
		{ "Spell", SpellType::kSpell },
		{ "Disease", SpellType::kDisease },
		{ "Power", SpellType::kPower },
		{ "LesserPower", SpellType::kLesserPower },
		{ "Ability", SpellType::kAbility },
		{ "Poison", SpellType::kPoison },
		{ "Enchantment", SpellType::kEnchantment },
		{ "Potion", SpellType::kPotion },
		{ "WortCraft", SpellType::kWortCraft },
		{ "LeveledSpell", SpellType::kLeveledSpell },
		{ "Addiction", SpellType::kAddiction },
		{ "VoicePower", SpellType::kVoicePower },
		{ "StaffEnchantment", SpellType::kStaffEnchantment },
		{ "Scroll", SpellType::kScroll },
	};

	using RE::MagicSystem::Delivery;

	template <>
	inline const util::enum_dict<Delivery> EnumLookup<Delivery> = {
		{ "Self", Delivery::kSelf },
		{ "Touch", Delivery::kTouch },
		{ "Aimed", Delivery::kAimed },
		{ "TargetActor", Delivery::kTargetActor },
		{ "TargetLocation", Delivery::kTargetLocation },
	};

	using RE::MagicSystem::CastingType;

	template <>
	inline const util::enum_dict<CastingType> EnumLookup<CastingType> = {
		{ "ConstantEffect", CastingType::kConstantEffect },
		{ "FireAndForget", CastingType::kFireAndForget },
		{ "Concentration", CastingType::kConcentration },
		{ "Scroll", CastingType::kScroll },
	};

	using EffectArchetype = RE::EffectArchetypes::ArchetypeID;

	template <>
	inline const util::enum_dict<EffectArchetype> EnumLookup<EffectArchetype> = {
		{ "ValueModifier", EffectArchetype::kValueModifier },
		{ "Script", EffectArchetype::kScript },
		{ "Dispel", EffectArchetype::kDispel },
		{ "CureDisease", EffectArchetype::kCureDisease },
		{ "Absorb", EffectArchetype::kAbsorb },
		{ "DualValueModifier", EffectArchetype::kDualValueModifier },
		{ "Calm", EffectArchetype::kCalm },
		{ "Demoralize", EffectArchetype::kDemoralize },
		{ "Frenzy", EffectArchetype::kFrenzy },
		{ "Disarm", EffectArchetype::kDisarm },
		{ "CommandSummoned", EffectArchetype::kCommandSummoned },
		{ "Invisibility", EffectArchetype::kInvisibility },
		{ "Light", EffectArchetype::kLight },
		{ "Darkness", EffectArchetype::kDarkness },
		{ "NightEye", EffectArchetype::kNightEye },
		{ "Lock", EffectArchetype::kLock },
		{ "Open", EffectArchetype::kOpen },
		{ "BoundWeapon", EffectArchetype::kBoundWeapon },
		{ "SummonCreature", EffectArchetype::kSummonCreature },
		{ "DetectLife", EffectArchetype::kDetectLife },
		{ "Telekinesis", EffectArchetype::kTelekinesis },
		{ "Paralysis", EffectArchetype::kParalysis },
		{ "Reanimate", EffectArchetype::kReanimate },
		{ "SoulTrap", EffectArchetype::kSoulTrap },
		{ "TurnUndead", EffectArchetype::kTurnUndead },
		{ "Guide", EffectArchetype::kGuide },
		{ "WerewolfFeed", EffectArchetype::kWerewolfFeed },
		{ "CureParalysis", EffectArchetype::kCureParalysis },
		{ "CureAddiction", EffectArchetype::kCureAddiction },
		{ "CurePoison", EffectArchetype::kCurePoison },
		{ "Concussion", EffectArchetype::kConcussion },
		{ "ValueAndParts", EffectArchetype::kValueAndParts },
		{ "AccumulateMagnitude", EffectArchetype::kAccumulateMagnitude },
		{ "Stagger", EffectArchetype::kStagger },
		{ "PeakValueModifier", EffectArchetype::kPeakValueModifier },
		{ "Cloak", EffectArchetype::kCloak },
		{ "Werewolf", EffectArchetype::kWerewolf },
		{ "SlowTime", EffectArchetype::kSlowTime },
		{ "Rally", EffectArchetype::kRally },
		{ "EnhanceWeapon", EffectArchetype::kEnhanceWeapon },
		{ "SpawnHazard", EffectArchetype::kSpawnHazard },
		{ "Etherealize", EffectArchetype::kEtherealize },
		{ "Banish", EffectArchetype::kBanish },
		{ "SpawnScriptedRef", EffectArchetype::kSpawnScriptedRef },
		{ "Disguise", EffectArchetype::kDisguise },
		{ "GrabActor", EffectArchetype::kGrabActor },
		{ "VampireLord", EffectArchetype::kVampireLord },
	};

	using EffectFlag = RE::EffectSetting::EffectSettingData::Flag;

	template <>
	inline const util::enum_dict<EffectFlag> EnumLookup<EffectFlag> = {
		{ "Hostile", EffectFlag::kHostile },
		{ "Recover", EffectFlag::kRecover },
		{ "Detrimental", EffectFlag::kDetrimental },
		{ "SnapToNavMesh", EffectFlag::kSnapToNavMesh },
		{ "NoHitEvent", EffectFlag::kNoHitEvent },
		{ "DispelWithKeywords", EffectFlag::kDispelWithKeywords },
		{ "NoDuration", EffectFlag::kNoDuration },
		{ "NoArea", EffectFlag::kNoArea },
		{ "FXPersist", EffectFlag::kFXPersist },
		{ "GoryVisuals", EffectFlag::kGoryVisuals },
		{ "HideInUI", EffectFlag::kHideInUI },
		{ "NoRecast", EffectFlag::kNoRecast },
		{ "PowerAffectsMagnitude", EffectFlag::kPowerAffectsMagnitude },
		{ "PowerAffectsDuration", EffectFlag::kPowerAffectsDuration },
		{ "Painless", EffectFlag::kPainless },
		{ "NoHitEffect", EffectFlag::kNoHitEffect },
		{ "NoDeathDispel", EffectFlag::kNoDeathDispel },
	};
}

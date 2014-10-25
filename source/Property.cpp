/*
 * Bael'Zharon's Respite
 * Copyright (C) 2014 Daniel Skorupski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; withuot even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include "Property.h"
#include <unordered_map>

static const unordered_map<uint32_t, string> kBoolProperties
{
    {0x0000, "undef"},
    {0x0001, "stuck"},
    {0x0002, "open"},
    {0x0003, "locked"},
    {0x0004, "rot proof"},
    {0x0005, "allegiance update request"},
    {0x0006, "ai uses mana"},
    {0x0007, "ai use human magic animations"},
    {0x0008, "allow give"},
    {0x0009, "currently attacking"},
    {0x000a, "attacker ai"},
    {0x000b, "ignore collisions"},
    {0x000c, "report collisions"},
    {0x000d, "ethereal"},
    {0x000e, "gravity status"},
    {0x000f, "lights status"},
    {0x0010, "scripted collision"},
    {0x0011, "inelastic"},
    {0x0012, "visibility"},
    {0x0013, "attackable"},
    {0x0014, "safe spell components"},
    {0x0015, "advocate state"},
    {0x0016, "inscribable"},
    {0x0017, "destroy on sell"},
    {0x0018, "ui hidden"},
    {0x0019, "ignore house barriers"},
    {0x001a, "hidden admin"},
    {0x001b, "pk wounder"},
    {0x001c, "pk killer"},
    {0x001d, "no corpse"},
    {0x001e, "under lifestone protection"},
    {0x001f, "item mana update pending"},
    {0x0020, "generator status"},
    {0x0021, "reset message pending"},
    {0x0022, "default open"},
    {0x0023, "default locked"},
    {0x0024, "default on"},
    {0x0025, "open for business"},
    {0x0026, "is frozen"},
    {0x0027, "deal magical items"},
    {0x0028, "logoff i'm dead"},
    {0x0029, "report collisions as environment"},
    {0x002a, "allow edge slide"},
    {0x002b, "advocate quest"},
    {0x002c, "is admin"},
    {0x002d, "is arch"},
    {0x002e, "is sentinel"},
    {0x002f, "is advocate"},
    {0x0030, "currently powering up"},
    {0x0031, "generator entered world"},
    {0x0032, "never fail casting"},
    {0x0033, "vendor service"},
    {0x0034, "ai immobile"},
    {0x0035, "damaged by collisions"},
    {0x0036, "is dynamic"},
    {0x0037, "is hot"},
    {0x0038, "is affecting"},
    {0x0039, "affects ais"},
    {0x003a, "spell queue active"},
    {0x003b, "generator disabled"},
    {0x003c, "is accepting tells"},
    {0x003d, "logging channel"},
    {0x003e, "opens any lock"},
    {0x003f, "unlimited use"},
    {0x0040, "generated treasure item"},
    {0x0041, "ignore magic resist"},
    {0x0042, "ignore magic armor"},
    {0x0043, "ai allow trade"},
    {0x0044, "spell components required"},
    {0x0045, "is sellable"},
    {0x0046, "ignore shields by skill"},
    {0x0047, "nodraw"},
    {0x0048, "activation untargeted"},
    {0x0049, "house has gotten priority boot pos"},
    {0x004a, "generator automatic destruction"},
    {0x004b, "house hooks visible"},
    {0x004c, "house requires monarch"},
    {0x004d, "house hooks enabled"},
    {0x004e, "house notified hud of hook count"},
    {0x004f, "ai accept everything"},
    {0x0050, "ignore portal restrictions"},
    {0x0051, "requires backpack slot"},
    {0x0052, "don't turn or move when giving"},
    {0x0053, "npc looks like object"},
    {0x0054, "ignore clo icons"},
    {0x0055, "appraisal has allowed wielder"},
    {0x0056, "chest regen on close"},
    {0x0057, "logoff in minigame"},
    {0x0058, "portal show destination"},
    {0x0059, "portal ignores pk attack timer"},
    {0x005a, "npc interacts silently"},
    {0x005b, "retained"},
    {0x005c, "ignore author"},
    {0x005d, "limbo"},
    {0x005e, "appraisal has allowed activator"},
    {0x005f, "existed before allegiance xp changes"},
    {0x0060, "is deaf"},
    {0x0061, "is psr"},
    {0x0062, "invincible"},
    {0x0063, "ivoryable"},
    {0x0064, "dyable"},
    {0x0065, "can generate rare"},
    {0x0066, "corpse generated rare"},
    {0x0067, "non projectile magic immune"},
    {0x0069, "actd received items"},
    {0x006a, "first enter world done"},
    {0x006b, "recalls disabled"},
    {0x006c, "rare uses timer"},
    {0x006d, "actd preorder received items"},
    {0x006e, "afk"},
    {0x006f, "is gagged"},
    {0x0070, "proc spell self targeted"},
    {0x0071, "is allegiance gagged"},
    {0x0072, "equipment set trigger piece"},
    {0x0073, "uninscribe"},
    {0x0074, "wield on use"},
    {0x0075, "chest cleared when closed"},
    {0x0076, "never attack"},
    {0x0077, "suppress generate effect"},
    {0x0078, "treasure corpse"},
    {0x0079, "equipment set add level"},
    {0x007a, "barber active"},
    {0x007b, "top layer priority"},
    {0x007c, "no held item shown"},
    {0x007d, "login at lifestone"},
    {0x007e, "olthoi pk"},
    {0x007f, "account 15 days"},
    {0x0080, "had no vitae"},
    {0x0081, "no olthoi talk"},
    {0x0082, "autowield left"}
};

static const unordered_map<uint32_t, string> kStringProperties
{
    {0x0000, "undef"},
    {0x0001, "time stamp format"},
    {0x0001, "name"},
    {0x0002, "title"},
    {0x0003, "sex"},
    {0x0004, "heritage group"},
    {0x0005, "template"},
    {0x0006, "attackers name"},
    {0x0007, "inscription"},
    {0x0008, "scribe name"},
    {0x0009, "vendors name"},
    {0x000a, "fellowship"},
    {0x000b, "monarchs name"},
    {0x000c, "lock code"},
    {0x000d, "key code"},
    {0x000e, "use"},
    {0x000f, "short desc"},
    {0x0010, "long desc"},
    {0x0011, "activation talk"},
    {0x0012, "use message"},
    {0x0013, "item heritage group restriction"},
    {0x0014, "plural name"},
    {0x0015, "monarchs title"},
    {0x0016, "activation failure"},
    {0x0016, "transient"},
    {0x0017, "scribe account"},
    {0x0018, "town name"},
    {0x0019, "craftsman name"},
    {0x001a, "use pk server error"},
    {0x001b, "score cached text"},
    {0x001c, "score default entry format"},
    {0x001d, "score first entry format"},
    {0x001e, "score last entry format"},
    {0x001f, "score only entry format"},
    {0x0020, "score no entry"},
    {0x0021, "quest"},
    {0x0022, "generator event"},
    {0x0023, "patrons title"},
    {0x0024, "house owner name"},
    {0x0025, "quest restriction"},
    {0x0026, "appraisal portal destination"},
    {0x0027, "tinker name"},
    {0x0028, "imbuer name"},
    {0x0029, "house owner account"},
    {0x0029, "db type"},
    {0x002a, "display name"},
    {0x002b, "date of birth"},
    {0x002c, "third party api"},
    {0x002d, "kill quest"},
    {0x002e, "afk"},
    {0x002f, "allegiance name"},
    {0x0030, "augmentation add quest"},
    {0x0031, "kill quest 2"},
    {0x0032, "kill quest 3"},
    {0x0033, "use sends signal"},
    {0x0034, "gear plating name"},
    {0xf62c, "textbox"}
};

static const unordered_map<uint32_t, string> kIntProperties
{
    {0x0000, "undef"},
    {0x0001, "item type"},
    {0x0002, "creature type"},
    {0x0003, "palette template"},
    {0x0004, "clothing priority"},
    {0x0005, "encumb val"},
    {0x0006, "items capacity"},
    {0x0007, "containers capacity"},
    {0x0008, "mass"},
    {0x0009, "locations"},
    {0x000a, "current wielded location"},
    {0x000b, "max stack size"},
    {0x000c, "stack size"},
    {0x000d, "stack unit encumb"},
    {0x000e, "stack unit mass"},
    {0x000f, "stack unit value"},
    {0x0010, "item useable"},
    {0x0011, "rare id"},
    {0x0012, "ui effects"},
    {0x0013, "value"},
    {0x0014, "coin value"},
    {0x0015, "total experience"},
    {0x0016, "available character"},
    {0x0017, "total skill credits"},
    {0x0018, "available skill credits"},
    {0x0019, "level"},
    {0x001a, "account requirements"},
    {0x001b, "armor type"},
    {0x001c, "armor level"},
    {0x001d, "allegiance cp pool"},
    {0x001e, "allegiance rank"},
    {0x001f, "channels allowed"},
    {0x0020, "channels active"},
    {0x0021, "bonded"},
    {0x0022, "monarchs rank"},
    {0x0023, "allegiance followers"},
    {0x0024, "resist magic"},
    {0x0025, "resist item appraisal"},
    {0x0026, "resist lockpick"},
    {0x0027, "deprecated resist repair"},
    {0x0028, "combat mode"},
    {0x0029, "current attack height"},
    {0x002a, "combat collisions"},
    {0x002b, "num deaths"},
    {0x002c, "damage"},
    {0x002d, "damage type"},
    {0x002e, "default combat style"},
    {0x002f, "attack type"},
    {0x0030, "weapon skill"},
    {0x0031, "weapon time"},
    {0x0032, "ammo type"},
    {0x0033, "combat use"},
    {0x0034, "parent location"},
    {0x0035, "placement position"},
    {0x0036, "weapon encumbrance"},
    {0x0037, "weapon mass"},
    {0x0038, "shield value"},
    {0x0039, "shield encumbrance"},
    {0x003a, "missile inventory location"},
    {0x003b, "full damage type"},
    {0x003c, "weapon range"},
    {0x003d, "attackers skill"},
    {0x003e, "defenders skill"},
    {0x003f, "attackers skill value"},
    {0x0040, "attackers class"},
    {0x0041, "placement"},
    {0x0042, "checkpoint status"},
    {0x0043, "tolerance"},
    {0x0044, "targeting tactic"},
    {0x0045, "combat tactic"},
    {0x0046, "homesick targeting tactic"},
    {0x0047, "num follow failures"},
    {0x0048, "friend type"},
    {0x0049, "foe type"},
    {0x004a, "merchandise item types"},
    {0x004b, "merchandise min value"},
    {0x004c, "merchandise max value"},
    {0x004d, "num items sold"},
    {0x004e, "num items bought"},
    {0x004f, "money income"},
    {0x0050, "money outflow"},
    {0x0051, "max generated objects"},
    {0x0052, "init generated objects"},
    {0x0053, "activation response"},
    {0x0054, "original value"},
    {0x0055, "num move failures"},
    {0x0056, "min level"},
    {0x0057, "max level"},
    {0x0058, "lockpick mod"},
    {0x0059, "booster enum"},
    {0x005a, "boost value"},
    {0x005b, "max structure"},
    {0x005c, "structure"},
    {0x005d, "physics state"},
    {0x005e, "target type"},
    {0x005f, "radarblip color"},
    {0x0060, "encumb capacity"},
    {0x0061, "login timestamp"},
    {0x0062, "creation timestamp"},
    {0x0063, "pk level modifier"},
    {0x0064, "generator type"},
    {0x0065, "ai allowed combat style"},
    {0x0066, "logoff timestamp"},
    {0x0067, "generator destruction type"},
    {0x0068, "activation create class"},
    {0x0069, "item workmanship"},
    {0x006a, "item spellcraft"},
    {0x006b, "item cur mana"},
    {0x006c, "item max mana"},
    {0x006d, "item difficulty"},
    {0x006e, "item allegiance rank limit"},
    {0x006f, "portal bitmask"},
    {0x0070, "advocate level"},
    {0x0071, "gender"},
    {0x0072, "attuned"},
    {0x0073, "item skill level limit"},
    {0x0074, "gate logic"},
    {0x0075, "item mana cost"},
    {0x0076, "logoff"},
    {0x0077, "active"},
    {0x0078, "attack height"},
    {0x0079, "num attack failures"},
    {0x007a, "ai cp threshold"},
    {0x007b, "ai advancement strategy"},
    {0x007c, "version"},
    {0x007d, "age"},
    {0x007e, "vendor happy mean"},
    {0x007f, "vendor happy variance"},
    {0x0080, "cloak status"},
    {0x0081, "vitae cp pool"},
    {0x0082, "num services sold"},
    {0x0083, "material type"},
    {0x0084, "num allegiance breaks"},
    {0x0085, "showable on radar"},
    {0x0086, "player killer status"},
    {0x0087, "vendor happy max items"},
    {0x0088, "score page num"},
    {0x0089, "score config num"},
    {0x008a, "score num scores"},
    {0x008b, "death level"},
    {0x008c, "ai options"},
    {0x008d, "open to everyone"},
    {0x008e, "generator time type"},
    {0x008f, "generator start time"},
    {0x0090, "generator end time"},
    {0x0091, "generator end destruction type"},
    {0x0092, "xp override"},
    {0x0093, "num crash and turns"},
    {0x0094, "component warning threshold"},
    {0x0095, "house status"},
    {0x0096, "hook placement"},
    {0x0097, "hook type"},
    {0x0098, "hook item type"},
    {0x0099, "ai pp threshold"},
    {0x009a, "generator version"},
    {0x009b, "house type"},
    {0x009c, "pickup emote offset"},
    {0x009d, "weenie iteration"},
    {0x009e, "wield requirements"},
    {0x009f, "wield skilltype"},
    {0x00a0, "wield difficulty"},
    {0x00a1, "house max hooks usable"},
    {0x00a2, "house current hooks usable"},
    {0x00a3, "allegiance min level"},
    {0x00a4, "allegiance max level"},
    {0x00a5, "house relink hook count"},
    {0x00a6, "slayer creature type"},
    {0x00a7, "confirmation in progress"},
    {0x00a8, "confirmation type in progress"},
    {0x00a9, "tsys mutation data"},
    {0x00aa, "num items in material"},
    {0x00ab, "num times tinkered"},
    {0x00ac, "appraisal long desc decoration"},
    {0x00ad, "appraisal lockpick success percent"},
    {0x00ae, "appraisal pages"},
    {0x00af, "appraisal max pages"},
    {0x00b0, "appraisal item skill"},
    {0x00b1, "gem count"},
    {0x00b2, "gem type"},
    {0x00b3, "imbued effect"},
    {0x00b4, "attackers raw skill value"},
    {0x00b5, "chess rank"},
    {0x00b6, "chess totalgames"},
    {0x00b7, "chess gameswon"},
    {0x00b8, "chess gameslost"},
    {0x00b9, "type of alteration"},
    {0x00ba, "skill to be altered"},
    {0x00bb, "skill alteration count"},
    {0x00bc, "heritage group"},
    {0x00bd, "transfer from attribute"},
    {0x00be, "transfer to attribute"},
    {0x00bf, "attribute transfer count"},
    {0x00c0, "fake fishing skill"},
    {0x00c1, "num keys"},
    {0x00c2, "death timestamp"},
    {0x00c3, "pk timestamp"},
    {0x00c4, "victim timestamp"},
    {0x00c5, "hook group"},
    {0x00c6, "allegiance swear timestamp"},
    {0x00c7, "house purchase timestamp"},
    {0x00c8, "redirectable equipped armor count"},
    {0x00c9, "meleedefense imbuedeffecttype cache"},
    {0x00ca, "missiledefense imbuedeffecttype cache"},
    {0x00cb, "magicdefense imbuedeffecttype cache"},
    {0x00cc, "elemental damage bonus"},
    {0x00cd, "imbue attempts"},
    {0x00ce, "imbue successes"},
    {0x00cf, "creature kills"},
    {0x00d0, "player kills pk"},
    {0x00d1, "player kills pkl"},
    {0x00d2, "rares tier one"},
    {0x00d3, "rares tier two"},
    {0x00d4, "rares tier three"},
    {0x00d5, "rares tier four"},
    {0x00d6, "rares tier five"},
    {0x00d7, "augmentation stat"},
    {0x00d8, "augmentation family stat"},
    {0x00d9, "augmentation innate family"},
    {0x00da, "augmentation innate strength"},
    {0x00db, "augmentation innate endurance"},
    {0x00dc, "augmentation innate coordination"},
    {0x00dd, "augmentation innate quickness"},
    {0x00de, "augmentation innate focus"},
    {0x00df, "augmentation innate self"},
    {0x00e0, "augmentation specialize salvaging"},
    {0x00e1, "augmentation specialize item tinkering"},
    {0x00e2, "augmentation specialize armor tinkering"},
    {0x00e3, "augmentation specialize magic item tinkering"},
    {0x00e4, "augmentation specialize weapon tinkering"},
    {0x00e5, "augmentation extra pack slot"},
    {0x00e6, "augmentation increased carrying capacity"},
    {0x00e7, "augmentation less death item loss"},
    {0x00e8, "augmentation spells remain past death"},
    {0x00e9, "augmentation critical defense"},
    {0x00ea, "augmentation bonus xp"},
    {0x00eb, "augmentation bonus salvage"},
    {0x00ec, "augmentation bonus imbue chance"},
    {0x00ed, "augmentation faster regen"},
    {0x00ee, "augmentation increased spell duration"},
    {0x00ef, "augmentation resistance family"},
    {0x00f0, "augmentation resistance slash"},
    {0x00f1, "augmentation resistance pierce"},
    {0x00f2, "augmentation resistance blunt"},
    {0x00f3, "augmentation resistance acid"},
    {0x00f4, "augmentation resistance fire"},
    {0x00f5, "augmentation resistance frost"},
    {0x00f6, "augmentation resistance lightning"},
    {0x00f7, "rares tier one login"},
    {0x00f8, "rares tier two login"},
    {0x00f9, "rares tier three login"},
    {0x00fa, "rares tier four login"},
    {0x00fb, "rares tier five login"},
    {0x00fc, "rares login timestamp"},
    {0x00fd, "rares tier six"},
    {0x00fe, "rares tier seven"},
    {0x00ff, "rares tier six login"},
    {0x0100, "rares tier seven login"},
    {0x0101, "item attribute limit"},
    {0x0102, "item attribute level limit"},
    {0x0103, "item attribute 2nd limit"},
    {0x0104, "item attribute 2nd level limit"},
    {0x0105, "character title id"},
    {0x0106, "num character titles"},
    {0x0107, "resistance modifier type"},
    {0x0108, "free tinkers bitfield"},
    {0x0109, "equipment set id"},
    {0x010a, "pet class"},
    {0x010b, "lifespan"},
    {0x010c, "remaining lifespan"},
    {0x010d, "use create quantity"},
    {0x010e, "wield requirements 2"},
    {0x010f, "wield skilltype 2"},
    {0x0110, "wield difficulty 2"},
    {0x0111, "wield requirements 3"},
    {0x0112, "wield skilltype 3"},
    {0x0113, "wield difficulty 3"},
    {0x0114, "wield requirements 4"},
    {0x0115, "wield skilltype 4"},
    {0x0116, "wield difficulty 4"},
    {0x0117, "unique"},
    {0x0118, "shared cooldown"},
    {0x0119, "faction 1 bits"},
    {0x011a, "faction 2 bits"},
    {0x011b, "faction 3 bits"},
    {0x011c, "hatred 1 bits"},
    {0x011d, "hatred 2 bits"},
    {0x011e, "hatred 3 bits"},
    {0x011f, "society rank celhan"},
    {0x0120, "society rank eldweb"},
    {0x0121, "society rank radblo"},
    {0x0122, "hear local signals"},
    {0x0123, "hear local signals radius"},
    {0x0124, "cleaving"},
    {0x0125, "augmentation specialize gearcraft"},
    {0x0126, "augmentation infused creature magic"},
    {0x0127, "augmentation infused item magic"},
    {0x0128, "augmentation infused life magic"},
    {0x0129, "augmentation infused war magic"},
    {0x012a, "augmentation critical expertise"},
    {0x012b, "augmentation critical power"},
    {0x012c, "augmentation skilled melee"},
    {0x012d, "augmentation skilled missile"},
    {0x012e, "augmentation skilled magic"},
    {0x012f, "imbued effect 2"},
    {0x0130, "imbued effect 3"},
    {0x0131, "imbued effect 4"},
    {0x0132, "imbued effect 5"},
    {0x0133, "damage rating"},
    {0x0134, "damage resist rating"},
    {0x0135, "augmentation damage bonus"},
    {0x0136, "augmentation damage reduction"},
    {0x0137, "imbue stacking bits"},
    {0x0138, "heal over time"},
    {0x0139, "crit rating"},
    {0x013a, "crit damage rating"},
    {0x013b, "crit resist rating"},
    {0x013c, "crit damage resist rating"},
    {0x013d, "healing resist rating"},
    {0x013e, "damage over time"},
    {0x013f, "item max level"},
    {0x0140, "item xp style"},
    {0x0141, "equipment set extra"},
    {0x0142, "aetheria bitfield"},
    {0x0143, "healing boost rating"},
    {0x0144, "heritage specific armor"},
    {0x0145, "alternate racial skills"},
    {0x0146, "augmentation jack of all trades"},
    {0x0147, "augmentation resistance nether"},
    {0x0148, "augmentation infused void magic"},
    {0x0149, "weakness rating"},
    {0x014a, "nether over time"},
    {0x014b, "nether resist rating"},
    {0x014c, "luminance award"},
    {0x014d, "lum aug damage rating"},
    {0x014e, "lum aug damage reduction rating"},
    {0x014f, "lum aug crit damage rating"},
    {0x0150, "lum aug crit reduction rating"},
    {0x0151, "lum aug surge effect rating"},
    {0x0152, "lum aug surge chance rating"},
    {0x0153, "lum aug item mana usage"},
    {0x0154, "lum aug item mana gain"},
    {0x0155, "lum aug vitality"},
    {0x0156, "lum aug healing rating"},
    {0x0157, "lum aug skilled craft"},
    {0x0158, "lum aug skilled spec"},
    {0x0159, "lum aug no destroy craft"},
    {0x015a, "restrict interaction"},
    {0x015b, "olthoi loot timestamp"},
    {0x015c, "olthoi loot step"},
    {0x015d, "use creates contract id"},
    {0x015e, "dot resist rating"},
    {0x015f, "life resist rating"},
    {0x0160, "cloak weave proc"},
    {0x0161, "weapon type"},
    {0x0162, "melee mastery"},
    {0x0163, "ranged mastery"},
    {0x0164, "sneak attack rating"},
    {0x0165, "recklessness rating"},
    {0x0166, "deception rating"},
    {0x0167, "combat pet range"},
    {0x0168, "weapon aura damage"},
    {0x0169, "weapon aura speed"},
    {0x016a, "summoning mastery"},
    {0x016b, "heartbeat lifespan"},
    {0x016c, "use level requirement"},
    {0x016d, "lum aug all skills"},
    {0x016e, "use requires skill"},
    {0x016f, "use requires skill level"},
    {0x0170, "use requires skill spec"},
    {0x0171, "use requires level"},
    {0x0172, "gear damage"},
    {0x0173, "gear damage resist"},
    {0x0174, "gear crit"},
    {0x0175, "gear crit resist"},
    {0x0176, "gear crit damage"},
    {0x0177, "gear crit damage resist"},
    {0x0178, "gear healing boost"},
    {0x0179, "gear nether resist"},
    {0x017a, "gear life resist"},
    {0x017b, "gear max health"}
};

static const unordered_map<uint32_t, string> kInt64Properties
{
    {0x0000, "undef"},
    {0x0001, "total experience"},
    {0x0002, "available experience"},
    {0x0003, "augmentation cost"},
    {0x0004, "item total xp"},
    {0x0005, "item base xp"},
    {0x0006, "available luminance"},
    {0x0007, "maximum luminance"},
    {0x0008, "interaction reqs"}
};

static const unordered_map<uint32_t, string> kFloatProperties
{
    {0x0000, "undef"},
    {0x0001, "heartbeat interval"},
    {0x0002, "heartbeat timestamp"},
    {0x0003, "health rate"},
    {0x0004, "stamina rate"},
    {0x0005, "mana rate"},
    {0x0006, "health upon resurrection"},
    {0x0007, "stamina upon resurrection"},
    {0x0008, "mana upon resurrection"},
    {0x0009, "start time"},
    {0x000a, "stop time"},
    {0x000b, "reset interval"},
    {0x000c, "shade"},
    {0x000d, "armor mod vs slash"},
    {0x000e, "armor mod vs pierce"},
    {0x000f, "armor mod vs bludgeon"},
    {0x0010, "armor mod vs cold"},
    {0x0011, "armor mod vs fire"},
    {0x0012, "armor mod vs acid"},
    {0x0013, "armor mod vs electric"},
    {0x0014, "combat speed"},
    {0x0015, "weapon length"},
    {0x0016, "damage variance"},
    {0x0017, "current power mod"},
    {0x0018, "accuracy mod"},
    {0x0019, "strength mod"},
    {0x001a, "maximum velocity"},
    {0x001b, "rotation speed"},
    {0x001c, "motion timestamp"},
    {0x001d, "weapon defense"},
    {0x001e, "wimpy level"},
    {0x001f, "visual awareness range"},
    {0x0020, "aural awareness range"},
    {0x0021, "perception level"},
    {0x0022, "powerup time"},
    {0x0023, "max charge distance"},
    {0x0024, "charge speed"},
    {0x0025, "buy price"},
    {0x0026, "sell price"},
    {0x0027, "default scale"},
    {0x0028, "lockpick mod"},
    {0x0029, "regeneration interval"},
    {0x002a, "regeneration timestamp"},
    {0x002b, "generator radius"},
    {0x002c, "time to rot"},
    {0x002d, "death timestamp"},
    {0x002e, "pk timestamp"},
    {0x002f, "victim timestamp"},
    {0x0030, "login timestamp"},
    {0x0031, "creation timestamp"},
    {0x0032, "minimum time since pk"},
    {0x0033, "deprecated housekeeping priority"},
    {0x0034, "abuse logging timestamp"},
    {0x0035, "last portal teleport timestamp"},
    {0x0036, "use radius"},
    {0x0037, "home radius"},
    {0x0038, "released timestamp"},
    {0x0039, "min home radius"},
    {0x003a, "facing"},
    {0x003b, "reset timestamp"},
    {0x003c, "logoff timestamp"},
    {0x003d, "econ recovery interval"},
    {0x003e, "weapon offense"},
    {0x003f, "damage mod"},
    {0x0040, "resist slash"},
    {0x0041, "resist pierce"},
    {0x0042, "resist bludgeon"},
    {0x0043, "resist fire"},
    {0x0044, "resist cold"},
    {0x0045, "resist acid"},
    {0x0046, "resist electric"},
    {0x0047, "resist health boost"},
    {0x0048, "resist stamina drain"},
    {0x0049, "resist stamina boost"},
    {0x004a, "resist mana drain"},
    {0x004b, "resist mana boost"},
    {0x004c, "translucency"},
    {0x004d, "physics script intensity"},
    {0x004e, "friction"},
    {0x004f, "elasticity"},
    {0x0050, "ai use magic delay"},
    {0x0051, "item min spellcraft mod"},
    {0x0052, "item max spellcraft mod"},
    {0x0053, "item rank probability"},
    {0x0054, "shade 2"},
    {0x0055, "shade 3"},
    {0x0056, "shade 4"},
    {0x0057, "item efficiency"},
    {0x0058, "item mana update timestamp"},
    {0x0059, "spell gesture speed mod"},
    {0x005a, "spell stance speed mod"},
    {0x005b, "allegiance appraisal timestamp"},
    {0x005c, "power level"},
    {0x005d, "accuracy level"},
    {0x005e, "attack angle"},
    {0x005f, "attack timestamp"},
    {0x0060, "checkpoint timestamp"},
    {0x0061, "sold timestamp"},
    {0x0062, "use timestamp"},
    {0x0063, "use lock timestamp"},
    {0x0064, "healkit mod"},
    {0x0065, "frozen timestamp"},
    {0x0066, "health rate mod"},
    {0x0067, "allegiance swear timestamp"},
    {0x0068, "obvious radar range"},
    {0x0069, "hotspot cycle time"},
    {0x006a, "hotspot cycle time variance"},
    {0x006b, "spam timestamp"},
    {0x006c, "spam rate"},
    {0x006d, "bond wielded treasure"},
    {0x006e, "bulk mod"},
    {0x006f, "size mod"},
    {0x0070, "gag timestamp"},
    {0x0071, "generator update timestamp"},
    {0x0072, "death spam timestamp"},
    {0x0073, "death spam rate"},
    {0x0074, "wild attack probability"},
    {0x0075, "focused probability"},
    {0x0076, "crash and turn probability"},
    {0x0077, "crash and turn radius"},
    {0x0078, "crash and turn bias"},
    {0x0079, "generator initial delay"},
    {0x007a, "ai acquire health"},
    {0x007b, "ai acquire stamina"},
    {0x007c, "ai acquire mana"},
    {0x007d, "resist health drain"},
    {0x007e, "lifestone protection timestamp"},
    {0x007f, "ai counteract enchantment"},
    {0x0080, "ai dispel enchantment"},
    {0x0081, "trade timestamp"},
    {0x0082, "ai targeted detection radius"},
    {0x0083, "emote priority"},
    {0x0084, "last teleport start timestamp"},
    {0x0085, "event spam timestamp"},
    {0x0086, "event spam rate"},
    {0x0087, "inventory offset"},
    {0x0088, "critical multiplier"},
    {0x0089, "mana stone destroy chance"},
    {0x008a, "slayer damage bonus"},
    {0x008b, "allegiance info spam timestamp"},
    {0x008c, "allegiance info spam rate"},
    {0x008d, "next spellcast timestamp"},
    {0x008e, "appraisal requested timestamp"},
    {0x008f, "appraisal heartbeat due timestamp"},
    {0x0090, "mana conversion mod"},
    {0x0091, "last pk attack timestamp"},
    {0x0092, "fellowship update timestamp"},
    {0x0093, "critical frequency"},
    {0x0094, "limbo start timestamp"},
    {0x0095, "weapon missile defense"},
    {0x0096, "weapon magic defense"},
    {0x0097, "ignore shield"},
    {0x0098, "elemental damage mod"},
    {0x0099, "start missile attack timestamp"},
    {0x009a, "last rare used timestamp"},
    {0x009b, "ignore armor"},
    {0x009c, "proc spell rate"},
    {0x009d, "resistance modifier"},
    {0x009e, "allegiance gag timestamp"},
    {0x009f, "absorb magic damage"},
    {0x00a0, "cached max absorb magic damage"},
    {0x00a1, "gag duration"},
    {0x00a2, "allegiance gag duration"},
    {0x00a3, "global xp mod"},
    {0x00a4, "healing modifier"},
    {0x00a5, "armor mod vs nether"},
    {0x00a6, "resist nether"},
    {0x00a7, "cooldown duration"},
    {0x00a8, "weapon aura offense"},
    {0x00a9, "weapon aura defense"},
    {0x00aa, "weapon aura elemental"},
    {0x00ab, "weapon aura mana conv"}
};

static const unordered_map<uint32_t, string> kPositionProperties
{
    {0x0000, "undef"},
    {0x0001, "location"},
    {0x0002, "destination"},
    {0x0003, "instantiation"},
    {0x0004, "sanctuary"},
    {0x0005, "home"},
    {0x0006, "activation move"},
    {0x0007, "target"},
    {0x0008, "linked portal one"},
    {0x0009, "last portal"},
    {0x000a, "portal storm"},
    {0x000b, "crash and turn"},
    {0x000c, "portal summon loc"},
    {0x000d, "house boot"},
    {0x000e, "last outside death"},
    {0x000f, "linked lifestone"},
    {0x0010, "linked portal two"},
    {0x0011, "save 1"},
    {0x0012, "save 2"},
    {0x0013, "save 3"},
    {0x0014, "save 4"},
    {0x0015, "save 5"},
    {0x0016, "save 6"},
    {0x0017, "save 7"},
    {0x0018, "save 8"},
    {0x0019, "save 9"},
    {0x001a, "relative destination"},
    {0x001b, "teleported character"}
};

static const unordered_map<uint32_t, string> kIIDProperties
{
    {0x0000, "invalid"},
    {0x0000, "undef"},
    {0x0001, "owner"},
    {0x0002, "container"},
    {0x0003, "wielder"},
    {0x0004, "freezer"},
    {0x0005, "viewer"},
    {0x0006, "generator"},
    {0x0007, "scribe"},
    {0x0008, "current combat target"},
    {0x0009, "current enemy"},
    {0x000a, "projectile launcher"},
    {0x000b, "current attacker"},
    {0x000c, "current damager"},
    {0x000d, "current follow target"},
    {0x000e, "current appraisal target"},
    {0x000f, "current fellowship appraisal target"},
    {0x0010, "activation target"},
    {0x0011, "creator"},
    {0x0012, "victim"},
    {0x0013, "killer"},
    {0x0014, "vendor"},
    {0x0015, "customer"},
    {0x0016, "bonded"},
    {0x0017, "wounder"},
    {0x0018, "allegiance"},
    {0x0019, "patron"},
    {0x001a, "monarch"},
    {0x001b, "combat target"},
    {0x001c, "health query target"},
    {0x001d, "last unlocker"},
    {0x001e, "crash and turn target"},
    {0x001f, "allowed activator"},
    {0x0020, "house owner"},
    {0x0021, "house"},
    {0x0022, "slumlord"},
    {0x0023, "mana query target"},
    {0x0024, "current game"},
    {0x0025, "requested appraisal target"},
    {0x0026, "allowed wielder"},
    {0x0027, "assigned target"},
    {0x0028, "limbo source"},
    {0x0029, "snooper"},
    {0x002a, "teleported character"},
    {0x002b, "pet"},
    {0x002c, "pet owner"},
    {0x002d, "pet device"}
};

static const unordered_map<uint32_t, string> kDIDProperties
{
    {0x0000, "undef"},
    {0x0001, "setup"},
    {0x0002, "motion table"},
    {0x0003, "sound table"},
    {0x0004, "combat table"},
    {0x0005, "quality filter"},
    {0x0006, "palette base"},
    {0x0007, "clothing base"},
    {0x0008, "icon"},
    {0x0009, "eyes texture"},
    {0x000a, "nose texture"},
    {0x000b, "mouth texture"},
    {0x000c, "default eyes texture"},
    {0x000d, "default nose texture"},
    {0x000e, "default mouth texture"},
    {0x000f, "hair palette"},
    {0x0010, "eyes palette"},
    {0x0011, "skin palette"},
    {0x0012, "head object"},
    {0x0013, "activation animation"},
    {0x0014, "init motion"},
    {0x0015, "activation sound"},
    {0x0016, "physics effect table"},
    {0x0017, "use sound"},
    {0x0018, "use target animation"},
    {0x0019, "use target success animation"},
    {0x001a, "use target failure animation"},
    {0x001b, "use user animation"},
    {0x001c, "spell"},
    {0x001d, "spell component"},
    {0x001e, "physics script"},
    {0x001f, "linked portal one"},
    {0x0020, "wielded treasure type"},
    {0x0023, "death treasure type"},
    {0x0024, "mutate filter"},
    {0x0025, "item skill limit"},
    {0x0026, "use create item"},
    {0x0027, "death spell"},
    {0x0028, "vendors class id"},
    {0x0029, "item specialized only"},
    {0x002a, "houseid"},
    {0x002b, "account house id"},
    {0x002c, "restriction effect"},
    {0x002d, "creation mutation filter"},
    {0x002e, "tsys mutation filter"},
    {0x002f, "last portal"},
    {0x0030, "linked portal two"},
    {0x0031, "original portal"},
    {0x0032, "icon overlay"},
    {0x0033, "icon overlay secondary"},
    {0x0034, "icon underlay"},
    {0x0035, "augmentation mutation filter"},
    {0x0036, "augmentation effect"},
    {0x0037, "proc spell"},
    {0x0038, "augmentation create item"},
    {0x0039, "alternate currency"},
    {0x003a, "blue surge spell"},
    {0x003b, "yellow surge spell"},
    {0x003c, "red surge spell"},
    {0x003d, "olthoi death treasure type"}
};

static const unordered_map<uint32_t, string> kSkillProperties
{
    {0x0000, "undef"},
    {0x0001, "axe"},
    {0x0002, "bow"},
    {0x0003, "crossbow"},
    {0x0004, "dagger"},
    {0x0005, "mace"},
    {0x0006, "melee defense"},
    {0x0007, "missile defense"},
    {0x0008, "sling"},
    {0x0009, "spear"},
    {0x000a, "staff"},
    {0x000b, "sword"},
    {0x000c, "thrown weapon"},
    {0x000d, "unarmed combat"},
    {0x000e, "arcane lore"},
    {0x000f, "magic defense"},
    {0x0010, "mana conversion"},
    {0x0011, "spellcraft"},
    {0x0012, "item appraisal"},
    {0x0013, "personal appraisal"},
    {0x0014, "deception"},
    {0x0015, "healing"},
    {0x0016, "jump"},
    {0x0017, "lockpick"},
    {0x0018, "run"},
    {0x0019, "awareness"},
    {0x001a, "arms and armor repair"},
    {0x001b, "creature appraisal"},
    {0x001c, "weapon appraisal"},
    {0x001d, "armor appraisal"},
    {0x001e, "magic item appraisal"},
    {0x001f, "creature enchantment"},
    {0x0020, "item enchantment"},
    {0x0021, "life magic"},
    {0x0022, "war magic"},
    {0x0023, "leadership"},
    {0x0024, "loyalty"},
    {0x0025, "fletching"},
    {0x0026, "alchemy"},
    {0x0027, "cooking"},
    {0x0028, "salvaging"},
    {0x0029, "two handed combat"},
    {0x002a, "gearcraft"},
    {0x002b, "void magic"},
    {0x002c, "heavy weapons"},
    {0x002d, "light weapons"},
    {0x002e, "finesse weapons"},
    {0x002f, "missile weapons"},
    {0x0030, "shield"},
    {0x0031, "dual wield"},
    {0x0032, "recklessness"},
    {0x0033, "sneak attack"},
    {0x0034, "dirty fighting"},
    {0x0035, "challenge"},
    {0x0036, "summoning"}
};

static const unordered_map<uint32_t, string> kAttributeProperties
{
    {0x0000, "undef"},
    {0x0001, "strength"},
    {0x0002, "endurance"},
    {0x0003, "quickness"},
    {0x0004, "coordination"},
    {0x0005, "focus"},
    {0x0006, "self"}
};

static const unordered_map<uint32_t, string> kAttribute2ndProperties
{
    {0x0000, "undef"},
    {0x0001, "max health"},
    {0x0002, "health"},
    {0x0003, "max stamina"},
    {0x0004, "stamina"},
    {0x0005, "max mana"},
    {0x0006, "mana"}
};

#define IMPLEMENT_GET(t) \
    const string& get##t##PropertyName(t##Property property) \
    { \
        auto it = k##t##Properties.find(static_cast<uint32_t>(property)); \
        if(it == k##t##Properties.end()) \
        { \
            throw runtime_error("unknown property"); \
        } \
        return it->second; \
    }

IMPLEMENT_GET(Bool);
IMPLEMENT_GET(String);
IMPLEMENT_GET(Int);
IMPLEMENT_GET(Int64);
IMPLEMENT_GET(Float);
IMPLEMENT_GET(Position);
IMPLEMENT_GET(IID);
IMPLEMENT_GET(DID);
IMPLEMENT_GET(Skill);
IMPLEMENT_GET(Attribute);
IMPLEMENT_GET(Attribute2nd);
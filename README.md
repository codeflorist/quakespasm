# QuakeSpasm-OpenVR

[![Latest Release](https://img.shields.io/github/v/release/gameflorist/quakespasm-openvr?display_name=tag&label=Download%20Latest%20Release&style=for-the-badge)](https://github.com/gameflorist/quakespasm-openvr/releases)

[![Windows Build Status](https://img.shields.io/github/actions/workflow/status/gameflorist/quakespasm-openvr/build-windows.yml?label=Windows%20Build%20Status&style=flat-square)](https://github.com/gameflorist/quakespasm-openvr/actions/workflows/build-windows.yml)

OpenVR support integrated into QuakeSpasm. The goal of this fork is primarily to keep it up-to-date with the current versions of QuakeSpasm and OpenVR. This allows maximized MOD support and support for the Enhanced Edition aka Re-Release of Quake.

There is however no big further development planned apart from minor features and bugfixes.

If your are looking for a much more feature rich VR experience, check out [Quake VR](https://github.com/vittorioromeo/quakevr) (see section below on differences between both projects).

Here are the changes to the last iterations of QuakeSpasm-OpenVR by [vittorioromero](https://github.com/vittorioromeo/Quakespasm-OpenVR/tree/wip) and [Fishbiter](https://github.com/Fishbiter/Quakespasm-OpenVR):

- Update to most current [QuakeSpasm](https://github.com/sezero/quakespasm) (v0.96.1)
- 64bit build
- Added head-based movment (in addition to controller-based movement)
- Fixed Multiplayer (Cross-Play with non-VR players should be possible!)
- Improved controller binding
- Support for [enhanced weapon models](#enhanced-models)
- Various other fixes and tweaks

## Quake VR vs QuakeSpasm-OpenVR?

Vittorio Romeo expanded `QuakeSpasm-OpenVR` considerably into the most excellent [Quake VR](https://github.com/vittorioromeo/quakevr), which is definitely a much more feature rich VR implementation - including teleportation, finger tracking, VR interactions, two-handed weapons, dual wielding, holsters and much more.

It is however a heavily modified version of QuakeSpasm, which is not compatible with enhanced mods (like Arcane Dimensions) out-of-the-box, and does not allow multiplayer-crossplay with non-VR players.

I would recommend you to enjoy [Quake VR](https://github.com/vittorioromeo/quakevr) primarily with vanilla Quake, it's official expansions as well as supported maps.

For a more bare-bone experience supporting all features of current QuakeSpasm (e.g. support for Arcane Dimensions and the Enhanced Edition), or cross-play multiplayer with non-VR-players QuakeSpasm-OpenVR would probably be the better option.

## History

This fork of [QuakeSpasm](https://github.com/sezero/quakespasm)...

- builds on the most current `QuakeSpasm-OpenVR` version from [vittorioromeo/Quakespasm-OpenVR](https://github.com/vittorioromeo/Quakespasm-OpenVR/tree/wip)
  - which was forked from [Fishbiter's improvement on Zackin5's version](https://github.com/Fishbiter/Quakespasm-OpenVR)
    - which was forked from [Zackin5's OpenVR port of Dominic Szablewski's (Phoboslab) Oculus modification of Quakespasm](https://github.com/Zackin5/Quakespasm-OpenVR)
      - which was forked from [Dominic Szablewski's (Phoboslab) Oculus modification of Quakespasm](https://github.com/phoboslab/Quakespasm-Rift) and utilizing the [OpenVR C wrapper by Ben Newhouse](https://github.com/newhouseb/openvr-c).

## Setup and Usage

Extract the most recent [release](https://github.com/gameflorist/quakespasm-openvr/releases) into your `Quake` or `Quake\rerelease` folder (where the subfolder `Id1` resides).

Launch `quakespasm-openvr.exe`.

### HD Textures

There is a [HD textures](https://drive.google.com/file/d/1UAH4la2uOv3lwMkMk05yZuYmiPIyExU_/view?usp=sharing) package available. Simply extract the zip-file into the `Id1` subfolder (where `PAK0.PAK` is located).

You can also download a HD texture pack for __Arcane Dimensions__ [here](https://www.moddb.com/games/quake/addons/hires-texture-pack-for-arcane-dimensions). Simply extract the `textures` folder into your `ad` directory.

### Enhanced Models

There are also 3 mods available containing enhanced models for enemies and weapons. These can also be used with QuakeSpasm-OpenVR.

- [__Plague's Weapon Pack for VR__](https://github.com/gameflorist/quake-plague-weapons-vr/releases):

  This pack contains the fully modelled weapons by [Plague](https://members.optusnet.com.au/%7eplaguespak/), adapted and animated for VR by Skizot, and expansion weapons added by codeflorist. This pack is perfect for VR.

  To use them with QuakeSpasm-OpenVR, extract `pakz.pak` into your `id1` subfolder and rename it by changing the `z` to a number higher then the highest existing `pak`-file inside your `id1` folder. If you are using `pak` files from vanilla Quake this will be `pak2.pak`, and if you're using the Re-Release, it will be `pak1.pak`.
  
  For the expansions, as as well as Arcane Dimensions, do exactly the same with the `hipnotic`, `rogue` and `ad` subfolders. There is also a special pack available for the Alkaline mod. Simply extract it into the `alk` subfolder.
  
  You will notice, that the weapon offsets and scaling will be off. To switch to the correct offsets, access the `VR Options` in Quake's main menu and switch `Gun Model Offsets` from `Vanilla` to `Plague`. (Note that you will have to do that for each expansion/add-on you load, since Quake writes separate configs per mod.)

- [__Enhanced Model Conversions Pack__](https://quakeone.com/forum/quake-mod-releases/finished-works/283295-osjc-s-enhanced-quake1-model-conversions-pack-v1):

  This pack is a conversion of the enhanced models from Quake's Re-Release. Models from the expansions are missing though. There are 2 ways to use it with QuakeSpasm-OpenVR:

  - Extract the `enhanced` folder of the downloaded archive into your `Quake` folder, and start the game with `-game enhanced`. This should automatically load vanilla Quake with the new models and correctly apply the correct weapon offsets.
  - If you want to use the new models globally with all expansions and add-ons, rename `pak0.pak` from the `enhanced` folder by changing the `0` to a number higher then the highest existing `pak`-file inside your `id1` folder. If you are using `pak` files from vanilla Quake this will be `pak2.pak`, and if you're using the Re-Release, it will be `pak1.pak`. You will notice, that the weapon offsets and scaling will be off. To switch to the correct offsets, access the `VR Options` in Quake's main menu and switch `Gun Model Offsets` from `Vanilla` to `Enhanced`. (Note that you will have to do that for each expansion/add-on you load, since Quake writes separate configs per mod.)

- [__Authentic Model Improvements__](https://github.com/NightFright2k19/quake_authmdl):

  This pack contains considerably more models as the one above - including converted ones from the Re-Release, but some weapons look worse than Plague's Weapon Pack and the Enhanced Model Conversion Pack linked above. To use them with QuakeSpasm-OpenVR, extract it into your `Quake` folder and rename the `pakz.pak` files by changing the `z` to a number higher then the highest existing `pak`-file inside your `id1`, `hipnotic`, and `rogue` folders. You will notice, that the weapon offsets and scaling will be off. To switch to the correct offsets, access the `VR Options` in Quake's main menu and switch `Gun Model Offsets` from `Vanilla` to `Authentic`. (Note that you will have to do that for each expansion/add-on you load, since Quake writes separate configs per mod.)

You can also use multiple MODs in conjunction. E.g. load the Authentic pack first as e.g. `pak1.pak` to get the wide arrange of models and then the Plague's Weapon Pack second e.g. as `pak2.pak` to get the better VR-optimized weapon models. Of course you have to set `Gun Model Offsets` to `Plague` in this case.

### Controls

Both head-based (default) and controller-based movement is supported. You can change it in the VR options.

Input from VR Controllers are mapped to various joystick-related input (except the left Application Menu button is bound to `ESCAPE`). The fork comes with the following reasonable default binding:

| Controller Button | Key Mapping | Default Action |
| ----------------- | ----------- | -------------- |
| Left Trigger | `LTRIGGER` | Jump |
| Right Trigger | `RTRIGGER` | Attack / Enter in Menu |
| Left Application Menu / B Button | `ESCAPE` | Toggle Menu / Escape |
| Right Application Menu / B Button | `BBUTTON` | Next Weapon |
| Left Pad/Stick Click | `LTHUMB` | Run |
| Right Pad/Stick Click | `RTHUMB` | Jump |
| Left Grip | `LSHOULDER` | Show Scores |
| Right Grip  | `RSHOULDER` |  Jump  |
| Left A Button | `ABUTTON` | Show Scores |
| Right A Button | `XBUTTON` | Previous Weapon |
| Right Axis 2 Press | `YBUTTON` | _none_ |
| Right Pad/Stick Up | `UPARROW` | _none_ |
| Right Pad/Stick Down | `DOWNARROW` | _none_ |
| Right Pad/Stick Left | `LEFTARROW` | _none_ |
| Right Pad/Stick Right | `RIGHTARROW` | _none_ |

#### Important infos:

- In SteamVR's default Legacy bindings, controllers with a dedicated `A` button (e.g. Index Controllers) cannot use this button independently from the `Grip` button. To change this, map `A Button` Click to `Left/Right A Button` instead of `Grip Button` in SteamVR's controller binding for `quakespasm-openvr.exe`. Now `A` buttons and `Grip` can be mapped independently.
- `Right Axis 2 Press` is not mapped at all in SteamVR's default Legacy bindings. You can bind it e.g. to the `Right Touchpad Click` to get an additional button.
- By default, the right pad/stick is configured for smooth/snap turning. If you use real roomscale-turning, you can set `Turn Speed` in the VR-Settings to the lowest setting (0) to turn this off. Then you can rebind the pad/stick like a D-Pad with 4 directions. You can use these 4 additional bindings e.g. for quick-loading/-saving or mapping of specific weapons.
- Check out the Community Binding `Index Controller Bindings` by `gameflorist` in SteamVR for a preset for Index Controllers, that makes the maximum buttons available for binding.

### Mission Packs, Add-Ons and Mods

All mission packs, add-ons and mods (supported by QuakeSpasm) should work out of the box. This includes:

- Scourge of Armagon
- Dissolution of Eternity
- Dimension of the Past
- Dimension of the Machine
- Arcane Dimensions (be sure to place it in a `ad` subfolder)
- [Alkaline](https://alkalinequake.wordpress.com/) (be sure to place it in a `alk` subfolder)
- etc.

As usual, expansion packs and mods are placed inside subfolders and then launched by stating the subfolder via the `game` parameter (e.g. `quakespasm-openvr.exe -game hipnotic`).

Quake Enhanced Edtion (aka Re-Release) stores it's Add-Ons in `C:\Users\<your-user>\Saved Games\Nightdive Studios\Quake\`. You have to copy the subfolders (e.g. `honey` or `q64`) of this folder into the folder where `quakespasm-openvr.exe` is located and launch the Add-On like stated above.

#### Known Issues

- Arcane Dimensions and Alkaline
  - When launching one of these mods, it will not display anything in VR at first. Press the __Enter__ key twice in order to get in game and play in VR.
- The Spiritworld
  - When launching this mod, it will not display anything in VR at first. Press the __Esc__ key and then the __Enter__ key twice in order to get in game and play in VR.
- Underdark Overbright & Copper
  - Water is rendered differently per eye in Underdark Overbright & Copper. The problem can be alleviated a bit by setting `r_wateralpha "0"` in your `config.cfg`.

### Cvars

- `vr_enabled` – 0: disabled, 1: enabled
- `vr_crosshair` – 0: disabled, 1: point, 2: laser sight
- `vr_crosshair_size` - Sets the diameter of the crosshair dot/laser from 1-32 pixels wide. Default 3.
- `vr_crosshair_depth` – Projection depth for the crosshair. Use `0` to automatically project on nearest wall/entity. Default 0.
- `vr_crosshair_alpha` – Sets the opacity for the crosshair dot/laser. Default 0.25.
- `vr_aimmode` – 7: Head Aiming, 2: Head Aiming + mouse pitch, 3: Mouse aiming, 4: Mouse aiming + mouse pitch, 5: Mouse aims, with YAW decoupled for limited area, 6: Mouse aims, with YAW decoupled for limited area and pitch decoupled completely, 7: controller attached. Default 7. (Note I haven't been very careful about maintaining these other modes, since they're obsolete from my point of view).
- `vr_deadzone` – Deadzone in degrees for `vr_aimmode 5`. Default 30.
- `vr_viewkick`– 0: disables viewkick on player damage/gun fire, 1: enable
- `vr_world_scale` - 1: Size of the player compared to normal quake character.
- `vr_floor_offset` - -16: height (in Quake units) of the player's origin off the ground (probably not useful to change)
- `vr_snap_turn` - 0: If 0, smooth turning, otherwise the size in degrees of each snap turn.

---
__New cvars for analog stick (and touchpad?) tuning on VR controllers.__ Default values should behave the same as before, but note that this version has not been tested with snap turning enabled. These have only been tested with analog sticks (Oculus Touch and Index Controllers), no idea how they behave with Vive touchpads.

- `vr_joystick_yaw_multi` - 1.0: Adjusts turn speed when using VR controllers, suggested 2.0-3.0
- `vr_joystick_axis_deadzone` - 0.25: Deadzone value for joysticks, suggested 0.1-0.2
- `vr_joystick_axis_exponent` - 1.0: Exponent for axis input, suggested 2.0. Larger numbers increase the 'low speed' portion of the movement range, numbers under 1.0: decrease it, 1.0 is linear response. 2.0 makes it easier to make fine adjustments at low speed
- `vr_joystick_deadzone_trunc` - 1 If enabled (value 1) then minimum movement speed will be given by the deadzone value, so it will be impossible to move at speeds below the deadzone value. When disabled (value 0) movement speed will ramp up from complete standstill to maximum speed while above the deadzone, so any speed is possible. Suggest setting to 0 to disable

### Note about weapons

Quake's weapons don't seem to be particularly consistently sized or offset. To work around this there are cvars to position/scale correct the weapons. Working default offsets are included for the following weapons:

- Vanilla Quake, Scourge of Armagon and Dissolution of Eternity weapons (including the VR versions of Plague's weapon pack and Enhanced and Authentic Model Packs - [see info above for details](#enhanced-models)!)
- Arcane Dimensions weapons (be sure to use folder-name `ad` and start game with `-game ad` to have them applied, [see info above for use of VR weapons](#enhanced-models))
- Alkaline weapons (be sure to use folder-name `alk` and start game with `-game alk` to have them applied, [see info above for use of VR weapons](#enhanced-models))
- Underdark Overbright's axe (be sure to use folder-name `udob` and start game with `-game udob` to have them applied)
- The Spiritworld's and axe (be sure to use folder-name `spiritworld` and start game with `-game spiritworld` to have them applied)

Unsupported mods may require new offsets. You can modify offsets by using the following cvars:

There are 20 slots for weapon VR offsets. There are 5 cvars for each (nn can be 01 to 20):

- `vr_wofs_id_nn` : The model name to offset (this name will be shown when equipping a weapon that doesn't have a VR offset
- `vr_wofs_scale_nn` : The model's scale
- `vr_wofs_x_nn` : X offset
- `vr_wofs_y_nn` : Y offset
- `vr_wofs_z_nn` : Z offset

Here are the `nn` values for all vanilla and mission pack weapons:

| Weapon | nn |
| ----------------- | ----------- |
| Axe | 01 |
| Shotgun | 02 |
| Super Shotgun | 03 |
| Nailgun | 04 |
| Super Nailgun | 05 |
| Grenade Launcher | 06 |
| Rocket Launcher | 07 |
| ___Scourge of Armagon (hipnotic):___ |
| Thunderbold | 08 |
| Mjolnir Hammer | 09 |
| Laser Cannon | 10 |
| Proximity Launcher | 11 |
| ___Dissolution of Eternity (rogue):___ |
| Lava Nailgun | 12 |
| Lava Super Nailgun | 13 |
| Multi Grenade Launcher | 14 |
| Multi Rocket Launcher | 15 |
| Plasma Gun | 16 |

You can place any modified cvars in an `autoexec.cfg` in the mod's directory to apply them for a mod, or in `id1` to apply them globally.

If you have found working values for a mod, feel free to create an issue, and i will try to include support for them out-of-the-box!

## Development and Building

### Merging current QuakeSpasm

Here is how to merge the current version of QuakeSpasm:

```git
git remote add sezero https://github.com/sezero/quakespasm.git
git fetch sezero --tags
git merge quakespasm-0.95.1 // use tag of new version to merge
```

### Building on Windows

Here is how to build this fork on Windows:

1. Install current version of Visual Studio (17.5.3 at the time of writing) with C++ workloads.
2. Open the file `.\Windows\VisualStudio\quakespasm.sln` in Visual Studio
3. Build `quakespasm-sdl2`.
4. As usual you also need a `id1` folder with a `PAK0.PAK` to be able to launch the game.

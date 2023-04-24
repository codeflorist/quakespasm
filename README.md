# Quakespasm-OpenVR

OpenVR support integrated into QuakeSpasm. The goal of this fork is primarily to keep it up-to-date with the current versions of QuakeSpasm and OpenVR. This allows maximized MOD support and support for the Enhanced Edition aka Re-Release of Quake.

There is however no big further development planned apart from minor features and bugfixes.

If your are looking for a much more feature rich VR experience, check out [Quake VR](https://github.com/vittorioromeo/quakevr) (see section below on differences between both projects). 

Here are the changes to the last iterations of Quakespasm-OpenVR by [vittorioromero](https://github.com/vittorioromeo/Quakespasm-OpenVR/tree/wip) and [Fishbiter](https://github.com/Fishbiter/Quakespasm-OpenVR):
- Update to most current [QuakeSpasm](https://github.com/sezero/quakespasm) (v0.95.1)
- 64bit build
- Added head-based movment (in addition to controller-based movement)
- Fixed Multiplayer (Cross-Play with non-VR players should be possible!)
- Improved controller binding
- Various other fixes and tweaks

## Quake VR vs Quakespasm-OpenVR?

Vittorio Romeo expanded `Quakespasm-OpenVR` considerably into the most excellent [Quake VR](https://github.com/vittorioromeo/quakevr), which is definitely a much more feature rich VR implementation - including teleportation, finger tracking, VR interactions, two-handed weapons, dual wielding, holsters and much more.

It is however a heavily modified version of QuakeSpasm, which is not compatible with enhanced mods (like Arcane Dimensions) out-of-the-box, and does not allow multiplayer-crossplay with non-VR players.

I would recommend you to enjoy [Quake VR](https://github.com/vittorioromeo/quakevr) primarily with vanilla Quake, it's official expansions as well as supported maps.

For a more bare-bone experience supporting all features of current QuakeSpasm (e.g. support for Arcane Dimensions and the Enhanced Edition), or cross-play multiplayer with non-VR-players Quakespasm-OpenVR would probably be the better option.

## History

This fork of [QuakeSpasm](https://github.com/sezero/quakespasm)...
- builds on the most current `Quakespasm-OpenVR` version from [vittorioromeo/Quakespasm-OpenVR](https://github.com/vittorioromeo/Quakespasm-OpenVR/tree/wip)
  - which was forked from [Fishbiter's improvement on Zackin5's version](https://github.com/Fishbiter/Quakespasm-OpenVR)
    - which was forked from [Zackin5's OpenVR port of Dominic Szablewski's (Phoboslab) Oculus modification of Quakespasm](https://github.com/Zackin5/Quakespasm-OpenVR)
      - which was forked from [Dominic Szablewski's (Phoboslab) Oculus modification of Quakespasm](https://github.com/phoboslab/Quakespasm-Rift) and utilizing the [OpenVR C wrapper by Ben Newhouse](https://github.com/newhouseb/openvr-c).

## Setup and Usage

Extract the most recent [release](https://github.com/codeflorist/quakespasm-openvr/releases) into your `Quake` or `Quake\rerelease` folder (where the subfolder `Id1` resides).

Launch `quakespasm-openvr.exe`.

### HD Textures

There is a [HD textures](https://drive.google.com/file/d/1UAH4la2uOv3lwMkMk05yZuYmiPIyExU_/view?usp=sharing) package available. Simply extract the zip-file into the `Id1` subfolder (where `PAK0.PAK` is located).

You can also download a HD texture pack for __Arcane Dimensions__ [here](https://www.moddb.com/games/quake/addons/hires-texture-pack-for-arcane-dimensions). Simply extract the `textures` folder into your `ad` directory.

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
- Arcane Dimensions
- etc.

As usual, expansion packs and mods are placed inside subfolders and then launched by stating the subfolder via the `game` parameter (e.g. `quakespasm-openvr.exe -game hipnotic`). This package comes included with a standard set of batch files for all expansion packs and the most common add-ons.

Quake Enhanced Edtion (aka Re-Release) stores it's Add-Ons in `C:\Users\<your-user>\Saved Games\Nightdive Studios\Quake\`. You have to copy the subfolders (e.g. `honey` or `q64`) of this folder into the folder where `quakespasm-openvr.exe` is located and launch the Add-On like stated above.

#### Known Issues

- Arcane Dimensions
  - When launching Arcane Dimensions it will not display anything in VR. Press the __Enter__ key twice in order to get in game and play in VR.

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

Quake's weapons don't seem to be particularly consistently sized or offset. To work around this there are cvars to position/scale correct the weapons. Set up for the default weapons are included but mods may require new offsets.

There are 20 slots for weapon VR offsets. There are 5 cvars for each (nn can be 01 to 20):

- `vr_wofs_id_nn` : The model name to offset (this name will be shown when equipping a weapon that doesn't have a VR offset
- `vr_wofs_scale_nn` : The model's scale
- `vr_wofs_x_nn` : X offset
- `vr_wofs_y_nn` : Y offset
- `vr_wofs_z_nn` : Z offset

You can place these in an autoexec.cfg in the mod's directory.

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

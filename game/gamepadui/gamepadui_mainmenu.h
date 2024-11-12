#ifndef GAMEPADUI_MAINMENU_H
#define GAMEPADUI_MAINMENU_H
#ifdef _WIN32
#pragma once
#endif

// clang-format off
#include "gamepadui_frame.h"
#include "gamepadui_button.h"
#include "gamepadui_image.h"
// clang-format on

namespace GamepadUIMenuStates {
enum GamepadUIMenuState {
  InGame,
  MainMenu,

  Count
};
}

using GamepadUIMenuState = GamepadUIMenuStates::GamepadUIMenuState;

class GamepadUIMainMenu : public GamepadUIFrame {
  DECLARE_CLASS_SIMPLE(GamepadUIMainMenu, GamepadUIFrame);

public:
  GamepadUIMainMenu(vgui::Panel *pParent);

  void ApplySchemeSettings(vgui::IScheme *pScheme) OVERRIDE;
  void OnCommand(char const *pCommand) OVERRIDE;
  void OnSetFocus() OVERRIDE;
  void UpdateGradients() OVERRIDE;

  void OnThink() OVERRIDE;
  void Paint() OVERRIDE;

  void LoadMenuButtons();
  void LayoutMainMenu();
  void PaintLogo();
  void OnMenuStateChanged();

  void OnKeyCodeReleased(vgui::KeyCode code);

private:
  void UpdateButtonVisibility();
  GamepadUIMenuState GetCurrentMenuState() const;
  CUtlVector<GamepadUIButton *> &GetCurrentButtons();
  float GetCurrentButtonOffset();
  float GetCurrentLogoOffset();

  CUtlVector<GamepadUIButton *> m_Buttons[GamepadUIMenuStates::Count];

#ifdef GAMEPADUI_GAME_EZ2
  GamepadUIButton *m_pSwitchToOldUIButton;

  GAMEPADUI_PANEL_PROPERTY(float, m_flOldUIButtonOffsetX, "OldUIButton.OffsetX",
                           "48", SchemeValueTypes::ProportionalFloat);
  GAMEPADUI_PANEL_PROPERTY(float, m_flOldUIButtonOffsetY, "OldUIButton.OffsetY",
                           "32", SchemeValueTypes::ProportionalFloat);
#endif

  GamepadUIString m_LogoText[2];
  GamepadUIImage m_LogoImage;

  /////// Animation stuff
  GAMEPADUI_PANEL_PROPERTY(float, m_flButtonsStartOffsetX,
                           "Buttons.OffsetX.Start", "0",
                           SchemeValueTypes::ProportionalFloat);
  GAMEPADUI_PANEL_PROPERTY(float, m_flButtonsAnimTime, "Buttons.AnimTime", "1",
                           SchemeValueTypes::Float);
  GAMEPADUI_PANEL_PROPERTY(float, m_flButtonsAnimTimeInGame,
                           "Buttons.AnimTime.InGame", "1",
                           SchemeValueTypes::Float);
  GAMEPADUI_PANEL_PROPERTY(float, m_flButtonsAnimPower, "Buttons.AnimPower",
                           "1", SchemeValueTypes::Float);
  GAMEPADUI_PANEL_PROPERTY(float, m_flButtonsAnimPowerInGame,
                           "Buttons.AnimPower.InGame", "1",
                           SchemeValueTypes::Float);

  GAMEPADUI_PANEL_PROPERTY(float, m_flLogoStartOffsetX, "Logo.OffsetX.Start",
                           "0", SchemeValueTypes::ProportionalFloat);
  GAMEPADUI_PANEL_PROPERTY(float, m_flLogoAnimTime, "Logo.AnimTime", "1",
                           SchemeValueTypes::Float);
  GAMEPADUI_PANEL_PROPERTY(float, m_flLogoAnimTimeInGame,
                           "Logo.AnimTime.InGame", "1",
                           SchemeValueTypes::Float);
  GAMEPADUI_PANEL_PROPERTY(float, m_flLogoAnimPower, "Logo.AnimPower", "1",
                           SchemeValueTypes::Float);
  GAMEPADUI_PANEL_PROPERTY(float, m_flLogoAnimPowerInGame,
                           "Logo.AnimPower.InGame", "1",
                           SchemeValueTypes::Float);
  ///////

  GAMEPADUI_PANEL_PROPERTY(float, m_flButtonSpacing, "Buttons.Space", "0",
                           SchemeValueTypes::ProportionalFloat);
  GAMEPADUI_PANEL_PROPERTY(float, m_flButtonsOffsetX, "Buttons.OffsetX", "0",
                           SchemeValueTypes::ProportionalFloat);

  GAMEPADUI_PANEL_PROPERTY(float, m_flButtonsOffsetYMenu,
                           "Buttons.OffsetY.MainMenu", "0",
                           SchemeValueTypes::ProportionalFloat);
  GAMEPADUI_PANEL_PROPERTY(float, m_flButtonsOffsetYInGame,
                           "Buttons.OffsetY.InGame", "0",
                           SchemeValueTypes::ProportionalFloat);

  GAMEPADUI_PANEL_PROPERTY(float, m_flLogoOffsetX, "Logo.OffsetX", "0",
                           SchemeValueTypes::ProportionalFloat);

  GAMEPADUI_PANEL_PROPERTY(float, m_flLogoOffsetYMenu, "Logo.OffsetY.MainMenu",
                           "0", SchemeValueTypes::ProportionalFloat);
  GAMEPADUI_PANEL_PROPERTY(float, m_flLogoOffsetYInGame, "Logo.OffsetY.InGame",
                           "0", SchemeValueTypes::ProportionalFloat);
  GAMEPADUI_PANEL_PROPERTY(float, m_flLogoSizeX, "Logo.SizeX", "0",
                           SchemeValueTypes::ProportionalFloat);
  GAMEPADUI_PANEL_PROPERTY(float, m_flLogoSizeY, "Logo.SizeY", "0",
                           SchemeValueTypes::ProportionalFloat);

  GAMEPADUI_PANEL_PROPERTY(Color, m_colLogoColor, "Logo", "255 255 255 255",
                           SchemeValueTypes::Color);
  GAMEPADUI_PANEL_PROPERTY(Color, m_colLogoNewColor, "NewLogo",
                           "255 134 44 255", SchemeValueTypes::Color);

  vgui::HFont m_hLogoFont;

#ifdef GAMEPADUI_GAME_EZ2
  GAMEPADUI_PANEL_PROPERTY(Color, m_colVersionColor, "Version", "255 128 0 255",
                           SchemeValueTypes::Color);
  GAMEPADUI_PANEL_PROPERTY(float, m_flVersionOffsetX, "Version.OffsetX", "16",
                           SchemeValueTypes::ProportionalFloat);

  vgui::HFont m_hVersionFont;

  GamepadUIString m_strEZ2Version;
#endif
};

#endif

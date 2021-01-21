/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2020 - Raw Material Software Limited

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 6 End-User License
   Agreement and JUCE Privacy Policy (both effective as of the 16th June 2020).

   End User License Agreement: www.juce.com/juce-6-licence
   Privacy Policy: www.juce.com/juce-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

namespace juce
{

/** Basic accessible interface for a Button which can be clicked or toggled.

    @tags{Accessibility}
*/
struct ButtonAccessibilityHandler  : public AccessibilityHandler
{
    explicit ButtonAccessibilityHandler (Button& buttonToWrap)
        : AccessibilityHandler (buttonToWrap,
                                AccessibilityRole::button,
                                buildAccessibilityActions (buttonToWrap)),
          button (buttonToWrap)
    {
    }

    AccessibleState getCurrentState() const override
    {
        auto state = AccessibilityHandler::getCurrentState();

        if (button.getClickingTogglesState() && button.getToggleState())
            return state.withToggled();

        return state;
    }

    String getTitle() const override  { return button.getButtonText(); }

private:
    static AccessibilityActions buildAccessibilityActions (Button& button)
    {
        auto actions = AccessibilityActions().addAction (AccessibilityActionType::press,
                                                         [&button] { button.triggerClick(); });

        if (button.getClickingTogglesState())
            return actions.addAction (AccessibilityActionType::toggle,
                                      [&button] { button.setToggleState (! button.getToggleState(), sendNotification); });

        return actions;
    }

    Button& button;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButtonAccessibilityHandler)
};

} // namespace juce

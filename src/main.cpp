#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

class $modify(InputManipulator, GJBaseGameLayer) {

    struct Fields {
        bool m_fake = false;
    };

    void handleButton(bool down, int button, bool player1) {

        // if mod disabled, do normal behavior
        if (!Mod::get()->getSettingValue<bool>("toggle")) {
            GJBaseGameLayer::handleButton(down, button, player1);
            return;
        }

        // stop recursion
        if (m_fields->m_fake) {
            GJBaseGameLayer::handleButton(down, button, player1);
            return;
        }

        m_fields->m_fake = true;

        // original input
        GJBaseGameLayer::handleButton(down, button, player1);

        // duplicate ONLY button presses
        if (down) {

            // fake release
            GJBaseGameLayer::handleButton(false, button, player1);

            // fake second press
            GJBaseGameLayer::handleButton(true, button, player1);
        }

        m_fields->m_fake = false;
    }
};

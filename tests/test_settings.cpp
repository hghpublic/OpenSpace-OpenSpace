/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2023                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <openspace/engine/settings.h>
#include <json/json.hpp>
#include <filesystem>
#include <fstream>

using namespace openspace;

TEST_CASE("Settings Load: Empty", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_empty.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    CHECK(!settings.visibility.has_value());
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Load: Really Empty", "[settings]") {
    constexpr std::string_view Source = R"(
{
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_really-empty.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    CHECK(!settings.visibility.has_value());
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Empty", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_empty.json";

    Settings srcSettings;
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Started Before", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "started-before": false
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_started-before.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    REQUIRE(settings.hasStartedBefore.has_value());
    CHECK(*settings.hasStartedBefore == false);
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    CHECK(!settings.visibility.has_value());
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Started Before", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_started-before.json";

    Settings srcSettings = {
        .hasStartedBefore = false
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Configuration", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "config": "abc"
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_config.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    REQUIRE(settings.configuration.has_value());
    CHECK(*settings.configuration == "abc");
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    CHECK(!settings.visibility.has_value());
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Configuration", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_config.json";

    Settings srcSettings = {
        .configuration = "abc"
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Configuration Remember", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "config-remember": true
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_config_remember.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    REQUIRE(settings.rememberLastConfiguration.has_value());
    CHECK(*settings.rememberLastConfiguration == true);
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    CHECK(!settings.visibility.has_value());
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Configuration Remember", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_config_remember.json";

    Settings srcSettings = {
        .rememberLastConfiguration = true
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Profile", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "profile": "def"
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_profile.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    REQUIRE(settings.profile.has_value());
    CHECK(*settings.profile == "def");
    CHECK(!settings.rememberLastProfile.has_value());
    CHECK(!settings.visibility.has_value());
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Profile", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_profile.json";

    Settings srcSettings = {
        .profile = "def"
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Profile Remember", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "profile-remember": false
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_profile_remember.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    REQUIRE(settings.rememberLastProfile.has_value());
    CHECK(*settings.rememberLastProfile == false);
    CHECK(!settings.visibility.has_value());
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Profile Remember", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_profile.json";

    Settings srcSettings = {
        .rememberLastProfile = false
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Visibility/NoviceUser", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "visibility": "NoviceUser"
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_visibility_novice.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    REQUIRE(settings.visibility.has_value());
    CHECK(*settings.visibility == properties::Property::Visibility::NoviceUser);
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Visibility/NoviceUser", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_noviceuser.json";

    Settings srcSettings = {
        .visibility = openspace::properties::Property::Visibility::NoviceUser
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Visibility/User", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "visibility": "User"
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_visibility_user.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    REQUIRE(settings.visibility.has_value());
    CHECK(*settings.visibility == properties::Property::Visibility::User);
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Visibility/User", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_user.json";

    Settings srcSettings = {
        .visibility = openspace::properties::Property::Visibility::User
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Visibility/AdvancedUser", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "visibility": "AdvancedUser"
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_visibility_advanced.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    REQUIRE(settings.visibility.has_value());
    CHECK(*settings.visibility == properties::Property::Visibility::AdvancedUser);
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Visibility/AdvancedUser", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_advanceduser.json";

    Settings srcSettings = {
        .visibility = openspace::properties::Property::Visibility::AdvancedUser
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Visibility/Developer", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "visibility": "Developer"
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_visibility_developer.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    REQUIRE(settings.visibility.has_value());
    CHECK(*settings.visibility == properties::Property::Visibility::Developer);
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Visibility/Developer", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_developer.json";

    Settings srcSettings = {
        .visibility = openspace::properties::Property::Visibility::Developer
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Bypass Launcher", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "bypass": false
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_bypass.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    CHECK(!settings.visibility.has_value());
    REQUIRE(settings.bypassLauncher.has_value());
    CHECK(*settings.bypassLauncher == false);
    CHECK(!settings.mrf.isEnabled.has_value());
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: Bypass Launcher", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_bypass.json";

    Settings srcSettings = {
        .bypassLauncher = false
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: MRF IsEnabled", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "mrf": {
        "enabled": true
    }
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_mrf_isenabled.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    CHECK(!settings.visibility.has_value());
    CHECK(!settings.bypassLauncher.has_value());
    REQUIRE(settings.mrf.isEnabled.has_value());
    CHECK(*settings.mrf.isEnabled == true);
    CHECK(!settings.mrf.location.has_value());
}

TEST_CASE("Settings Save: MRF IsEnabled", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_mrf_isenabled.json";

    Settings srcSettings = {
        .mrf = Settings::MRF {
            .isEnabled = true
        }
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: MRF Location", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "mrf": {
        "location": "ghi"
    }
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_mrf_location.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    CHECK(!settings.hasStartedBefore.has_value());
    CHECK(!settings.configuration.has_value());
    CHECK(!settings.rememberLastConfiguration.has_value());
    CHECK(!settings.profile.has_value());
    CHECK(!settings.rememberLastProfile.has_value());
    CHECK(!settings.visibility.has_value());
    CHECK(!settings.bypassLauncher.has_value());
    CHECK(!settings.mrf.isEnabled.has_value());
    REQUIRE(settings.mrf.location.has_value());
    CHECK(*settings.mrf.location == "ghi");
}

TEST_CASE("Settings Save: MRF Location", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_mrf_location.json";

    Settings srcSettings = {
        .mrf = Settings::MRF {
            .location = "ghi"
        }
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load: Full", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "started-before": false,
    "config": "abc",
    "config-remember": true,
    "profile": "def",
    "profile-remember": false,
    "visibility": "NoviceUser",
    "bypass": false,
    "mrf": {
        "enabled": true,
        "location": "ghi"
    }
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_full.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    Settings settings = loadSettings(file);

    REQUIRE(settings.hasStartedBefore.has_value());
    CHECK(*settings.hasStartedBefore == false);
    REQUIRE(settings.configuration.has_value());
    CHECK(*settings.configuration == "abc");
    REQUIRE(settings.rememberLastConfiguration.has_value());
    CHECK(*settings.rememberLastConfiguration == true);
    REQUIRE(settings.profile.has_value());
    CHECK(*settings.profile == "def");
    REQUIRE(settings.rememberLastProfile.has_value());
    CHECK(*settings.rememberLastProfile == false);
    REQUIRE(settings.visibility.has_value());
    CHECK(*settings.visibility == properties::Property::Visibility::NoviceUser);
    REQUIRE(settings.bypassLauncher.has_value());
    CHECK(*settings.bypassLauncher == false);
    REQUIRE(settings.mrf.isEnabled.has_value());
    CHECK(*settings.mrf.isEnabled == true);
    REQUIRE(settings.mrf.location.has_value());
    CHECK(*settings.mrf.location == "ghi");
}

TEST_CASE("Settings Save: Full", "[settings]") {
    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_save_full.json";

    Settings srcSettings = {
        .hasStartedBefore = false,
        .configuration = "abc",
        .rememberLastConfiguration = true,
        .profile = "def",
        .rememberLastProfile = false,
        .visibility = openspace::properties::Property::Visibility::NoviceUser,
        .bypassLauncher = false,
        .mrf = Settings::MRF {
            .isEnabled = true,
            .location = "ghi"
        }
    };
    saveSettings(srcSettings, file);

    Settings cmpSettings = loadSettings(file);
    CHECK(srcSettings == cmpSettings);
}

TEST_CASE("Settings Load Fail: Illegal version", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": -1
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_fail_illegal_version.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    CHECK_THROWS(loadSettings(file));
}

TEST_CASE("Settings Load Fail: Started before", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "started-before": "abc"
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_fail_started-before.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    CHECK_THROWS(loadSettings(file));
}

TEST_CASE("Settings Load Fail: Config", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "config": 1
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_fail_config.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    CHECK_THROWS(loadSettings(file));
}

TEST_CASE("Settings Load Fail: Profile", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "profile": 1
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_fail_profile.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    CHECK_THROWS(loadSettings(file));
}

TEST_CASE("Settings Load Fail: Visibility type", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "visibility": 1
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_fail_visibility_type.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    CHECK_THROWS(loadSettings(file));
}

TEST_CASE("Settings Load Fail: Visibility value", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "visibility": "abc"
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_fail_visibility_value.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    CHECK_THROWS(loadSettings(file));
}

TEST_CASE("Settings Load Fail: Bypass Launcher", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "bypass": 1
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_fail_bypass.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    CHECK_THROWS(loadSettings(file));
}

TEST_CASE("Settings Load Fail: MRF", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "mrf": 1
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_fail_mrf.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    CHECK_THROWS(loadSettings(file));
}

TEST_CASE("Settings Load Fail: MRF/enabled", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "mrf": {
        "enabled": 1
    }
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_fail_mrf_enabled.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    CHECK_THROWS(loadSettings(file));
}

TEST_CASE("Settings Load Fail: MRF/location", "[settings]") {
    constexpr std::string_view Source = R"(
{
    "version": 1,
    "mrf": {
        "location": 1
    }
}
)";

    std::filesystem::path path = std::filesystem::temp_directory_path();
    std::filesystem::path file = path / "test_settings_load_fail_mrf_location.json";
    {
        std::ofstream f(file);
        f << Source;
    }

    CHECK_THROWS(loadSettings(file));
}
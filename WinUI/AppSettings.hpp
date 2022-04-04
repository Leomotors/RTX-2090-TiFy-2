#pragma once

namespace winrt::RTX_2090_TiFy {

class AppSettings {
  public:
    AppSettings() = delete;
    static const hstring Theme;
    static int32_t CurrentTheme;
};

}  // namespace winrt::RTX_2090_TiFy
#include "pch.h"
#include "HomePage.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif

#include "AppState.hpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::RTX_2090_TiFy::implementation {

HomePage::HomePage() { InitializeComponent(); }

fire_and_forget HomePage::SelectInput_Click(IInspectable const& sender,
                                            RoutedEventArgs const& e) {
    using namespace Windows::Storage;
    using namespace Windows::Storage::Pickers;
    using namespace Windows::UI::Xaml::Media;

    auto picker = FileOpenPicker();
    picker.ViewMode(PickerViewMode::Thumbnail);
    picker.SuggestedStartLocation(PickerLocationId::PicturesLibrary);
    picker.FileTypeFilter().Append(L".jpg");
    picker.FileTypeFilter().Append(L".jpeg");
    picker.FileTypeFilter().Append(L".png");

    InputLoadProgress().Visibility(Visibility::Visible);

    auto file = co_await picker.PickSingleFileAsync();

    if (!file) {
        InputLoadProgress().Visibility(Visibility::Collapsed);
        co_return;
    }

    auto folder = ApplicationData::Current().TemporaryFolder();

    auto localCopy = co_await file.CopyAsync(
        folder, file.Name(), NameCollisionOption::ReplaceExisting);

    InputImage().Source(Imaging::BitmapImage(Uri(localCopy.Path())));

    AppState::ImageHandler.loadImage(to_string(localCopy.Path()));

    InputLoadProgress().Visibility(Visibility::Collapsed);
}

}  // namespace winrt::RTX_2090_TiFy::implementation

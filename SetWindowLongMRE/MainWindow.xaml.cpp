#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <microsoft.ui.xaml.window.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::SetWindowLongMRE::implementation
{
    MainWindow::MainWindow()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    winrt::fire_and_forget MainWindow::myButton_Click2(IInspectable const&, RoutedEventArgs const&)
    {
        using namespace winrt::Windows::Media::Audio;
        AudioGraphSettings settings{ winrt::Windows::Media::Render::AudioRenderCategory::Media };
        CreateAudioGraphResult result = co_await AudioGraph::CreateAsync(settings);
        WINRT_ASSERT(result.Status() == AudioGraphCreationStatus::Success);
        auto m_audioGraph = result.Graph();
        auto m_frameOutputNode = m_audioGraph.CreateFrameOutputNode(/*m_audioGraph.EncodingProperties()*/);
        auto deviceInputNodeResult = co_await m_audioGraph.CreateDeviceInputNodeAsync(
            winrt::Windows::Media::Capture::MediaCategory::Media
            /*, m_audioGraph.EncodingProperties()*/
        );
    }
    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        winrt::Microsoft::UI::Xaml::Window window{ *this };
        winrt::com_ptr<IWindowNative> windowNative = window.as<IWindowNative>();
        HWND hwnd{};
        windowNative->get_WindowHandle(&hwnd);
        SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW & ~(WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME));
        ShowWindow(hwnd, SW_MAXIMIZE);
        myButton().Content(box_value(L"Clicked"));
    }


}

## Setup
Before building, install the VirtualBox and Qt SDK along with setting the paths:
1. Download and install the [VirtualBox SDK](https://www.virtualbox.org/wiki/Downloads#VirtualBox5.2.12SoftwareDeveloperKitSDK)
2. Create the props file (Clone repo and load project in Visual Studio 2017 if not done already)
   1. Enable the Property Manager view [**View** -> **Other Windows** -> **Property Manager**]
   2. Right click **VBMGUI** and select **Add New Project Property Sheet...**
   3. Name the file **VBOXSDK_path.props**
   4. Double click **VBOXSDK_path.props** (Debug vs. Release doesn't matter) and click **User Macros** on the left; click **Add Macro**
   5. Set the name to **VBOX_SDK** and set the value to the path of the SDK down to the **mscom** folder (e.g. C:\Dev\SDKs\VirtualBoxSDK-5.2.8-121009\sdk\bindings\mscom)
3. Download and install version **5.10.1 (MSVC 2017 64-bit)** of the [Qt SDK](https://www.qt.io/download)
4. Install and setup **Qt Visual Studio Tools** from the Visual Studio extension manager
   1. Add the Qt version to Qt VS Tools [**Qt VS Tools** -> **Qt Options**]
5. Build!
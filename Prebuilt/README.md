# Prebuilt
Here you'll find pre-built plug-ins (click links to download):
 * [ShowMIDI_CC_MacAU_64.zip](https://github.com/getdunne/ShowMIDI/raw/master/Prebuilt/ShowMIDI_CC_MacAU_64.zip) Audio Unit (Mac *.component* file), 64-bit
 * [ShowMIDI_CC_MacVST_64.zip](https://github.com/getdunne/ShowMIDI/raw/master/Prebuilt/ShowMIDI_CC_MacVST_64.zip) VST (v2, Mac *.vst* file), 64-bit
 * [ShowMIDI_CC_WinVST.zip](https://github.com/getdunne/ShowMIDI/raw/master/Prebuilt/ShowMIDI_CC_WinVST.zip) VST(v2, Windows *.dll* files), 32- and 64-bit

On the Mac, put the *.component* file in *~/Library/Audio/Plug-Ins/Components*, and note with recent versions of macOS *you must log out and back in again* before the plug-in will be visible to Logic Pro X and other Audio-Unit hosts.

On the Mac, put the *.vst* file in *~/Library/Audio/Plug-Ins/VST*.

On Windows, put the *.dll* file wherever your VST host program looks for plug-ins.

## Acknowledgements

![](VST2LogoWhite.jpg "VST2 logo") ![](VST3LogoBlack.jpg "VST3 logo")

*VST* and its expansion *Virtual Studio Technologies* are registered trade marks of [Steinberg Media Technologies GmbH](https://www.steinberg.net/) and are used under license.

---

![](JUCE-logo.png) ![](gplv3-with-text-136x68.png)

This program was developed with [JUCE 5.x](https://shop.juce.com/get-juce), hence subject to the [GNU GPL v3 license](https://www.gnu.org/licenses/gpl-3.0.en.html). Use the *Projucer* to generate the necessary projects, e.g. VST2 for Windows, Audio Unit for Mac. To build VST/VST3 you'll need the [VST3 SDK](https://github.com/steinbergmedia/vst3sdk) from Steinberg. To distribute finished products, you may need a [license](https://www.steinberg.net/en/company/developers.html).

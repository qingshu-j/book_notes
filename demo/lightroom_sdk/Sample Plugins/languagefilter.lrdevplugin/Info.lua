--[[----------------------------------------------------------------------------

Info.lua
Summary information for language filter plug-in

--------------------------------------------------------------------------------

ADOBE SYSTEMS INCORPORATED
 Copyright 2008 Adobe Systems Incorporated
 All Rights Reserved.

NOTICE: Adobe permits you to use, modify, and distribute this file in accordance
with the terms of the Adobe license agreement accompanying it. If you have received
this file from a source other than Adobe, then your use, modification, or distribution
of it requires the prior written permission of Adobe.


------------------------------------------------------------------------------]]

return {

	LrSdkVersion = 3.0,
	LrSdkMinimumVersion = 2.0,

	LrPluginName = "Language External Tool",
	LrToolkitIdentifier = 'com.adobe.lightroom.sdk.export.language',
	
	LrExportFilterProvider = {
		title = "Language External Tool",
		file = 'LanguageExternalToolFilterProvider.lua',
	},

	VERSION = { major=13, minor=2, revision=0, build="202402141005-bf1aeb84", },

}

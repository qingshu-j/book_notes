--[[----------------------------------------------------------------------------

Info.lua
Summary information for custom metadata sample plugin

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
	LrToolkitIdentifier = 'com.adobe.lightroom.sdk.metadata.custommetadatasample',

	LrPluginName = LOC "$$$/CustomMetadata/PluginName=Custom Metadata Sample",
	LrPluginInfoUrl = "http://www.adobe.com",
	
	-- Add the Metadata Definition File
	LrMetadataProvider = 'CustomMetadataDefinition.lua',
	
	-- Add the Metadata Tagset File
	LrMetadataTagsetFactory = {
		'CustomMetadataTagset.lua',
		'AllMetadataTagset.lua',
	},

	LrLibraryMenuItems = {
		title = 'Custom Metadata Dialog',
		file = 'DisplayMetadata.lua',
		enabledWhen = 'photosAvailable',
	},
	
	-- Add the entry for the Plug-in Manager Dialog
	LrPluginInfoProvider = 'PluginInfoProvider.lua',
	
	VERSION = { major=13, minor=2, revision=0, build="202402141005-bf1aeb84", },

}

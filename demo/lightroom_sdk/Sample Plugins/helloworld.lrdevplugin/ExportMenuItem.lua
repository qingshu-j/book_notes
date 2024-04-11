--[[----------------------------------------------------------------------------

ADOBE SYSTEMS INCORPORATED
 Copyright 2007 Adobe Systems Incorporated
 All Rights Reserved.

NOTICE: Adobe permits you to use, modify, and distribute this file in accordance
with the terms of the Adobe license agreement accompanying it. If you have received
this file from a source other than Adobe, then your use, modification, or distribution
of it requires the prior written permission of Adobe.

--------------------------------------------------------------------------------

ExportMenuItem.lua
From the Hello World sample plug-in. Displays a modal dialog and writes debug info.

------------------------------------------------------------------------------]]

-- Access the Lightroom SDK namespaces.
local LrApplication = import 'LrApplication'
local LrDialogs = import 'LrDialogs'
local LrLogger = import 'LrLogger'
local LrTasks = import 'LrTasks'

-- Create the logger and enable the print function.
local myLogger = LrLogger( 'exportLogger' )
myLogger:enable( "logfile" ) -- Pass either a string or a table of actions.

--------------------------------------------------------------------------------
-- Write trace information to the logger.

local function outputToLog( message )
	myLogger:trace( message )
end

--------------------------------------------------------------------------------
-- Display a modal information dialog.

local function showModalDialog()

	--outputToLog( "MyHWExportItem.showModalMessage function entered." )
	--LrDialogs.message( "ExportMenuItem Selected", "Hello World!", "info" );
	--outputToLog( "MyHWExportItem.showModalMessage function exiting." )
	--[[
	    -- 弹出对话框选择目录
    local result = LrDialogs.runOpenPanel {
        title = "选择目录",
        canChooseFiles = false,
        canChooseDirectories = true,
        canCreateDirectories = true,
        prompt = "选择要打开的目录"
    }

    -- 如果选择了目录，则打开该目录
    if result and #result > 0 then
        local selectedFolder = result[1]
        LrApplication.openCatalog(selectedFolder)
    end
	--]]
	    -- 获取 Lightroom 应用程序对象
    --local app = LrApplication.activeCatalog()

    -- 获取当前活动的窗口
    --local activeWindow = app:activeView()

    -- 隐藏工具栏
    --activeWindow:setProperty('showToolbar', false)
	
end


--local LrApplication = import 'LrApplication'
--local LrTasks = import 'LrTasks'

local function AdjustTemperature()

	outputToLog( "enter AdjustTemperature func." )
    -- 获取 Lightroom 应用程序对象
    local app = LrApplication.activeCatalog()

    -- 获取当前选中的照片
    local selectedPhotos = app:getTargetPhotos()
	local mylen = #selectedPhotos
	outputToLog(mylen)
    -- 如果没有选中照片，则弹出提示框
    if not selectedPhotos or #selectedPhotos == 0 then
        LrDialogs.showError("请先选中要调整色温的照片")
        return
    end

	outputToLog( "enter applyDevelopPreset." )
    -- 应用修改色温的设置到选中的照片
    for _, photo in ipairs(selectedPhotos) do
		local catalog = LrApplication.activeCatalog()
		LrTasks.startAsyncTask( function()
		catalog:withWriteAccessDo( 'myTask', function()
		--photo:quickDevelopAdjustImage("Saturation",50)
		--photo:quickDevelopAdjustWhiteBalance("Tint",50)
		--photo:quickDevelopSetTreatment("grayscale") 
		--photo:quickDevelopSetWhiteBalance("Tungsten")
		--photo:rotateLeft()
		photo:openExportDialog ()
		local settings = photo:getDevelopSettings()
		--local myString = table.concat(settings, "|")
		local br = settings['Contrast']
		outputToLog(br)
		settings['Contrast'] = 89
		--photo:applyDevelopSettings(settings)
		local settingsa = photo:getDevelopSettings()
		outputToLog(settings['Contrast'])
		--local preset = LrApplication.addDevelopPresetForPlugin( _PLUGIN, "___Dummy___", settings)
        --photo:applyDevelopPreset(preset)
		end)
		end)
    end
	outputToLog( "end applyDevelopPreset." )
    -- 提示用户调整完成
    LrTasks.startAsyncTask(function()
        LrDialogs.showBezel("照片色温调整完成")
    end)

end

AdjustTemperature()

--------------------------------------------------------------------------------
-- Display a dialog.
--showModalDialog()



-- Command line: ./InitPlugin.lua

-- params : ...
-- function num : 0
local LrApplication = import("LrApplication")
local LrApplicationView = import("LrApplicationView")
local LrDevelopController = import("LrDevelopController")
local LrDialogs = import("LrDialogs")
local LrFileUtils = import("LrFileUtils")
local LrFunctionContext = import("LrFunctionContext")
local LrPathUtils = import("LrPathUtils")
local LrSocket = import("LrSocket")
local LrTasks = import("LrTasks")
local commandQuerySet = {}
local isTimerStarted = false
local commandResultDic = {}
local LrDevelopController = import("LrDevelopController")
if not (string.find)(((import("LrSystemInfo")).osVersion)(), "Windows") or not LrDevelopController.revealPanel then
  revealOSSpecificPanel = LrDevelopController.revealPanelIfVisible
end

local lineBreak = "\n"
require("Globals")
-- DECOMPILER ERROR at PC60: Confused about usage of register: R14 in 'UnsetPending'

if (plugin.prefs).showBezel == nil then
(plugin.prefs).showBezel = true
end
local lastitem = nil
local lrcMajorVersion = ((LrApplication.versionTable)()).major
local isSDKGreater11 = tonumber(lrcMajorVersion) >= 11
GetPreciseDecimal = function(nNum, n)
-- function num : 0_0
if type(nNum) ~= "number" then
return nNum
end
if not n then
n = 0
end
n = (math.floor)(n)
if n < 0 then
n = 0
end
local nDecimal = 10 ^ n
local nTemp = (math.floor)(nNum * nDecimal)
local nRet = nTemp / nDecimal
return nRet
end

changeAdjustmentValue = function(item, showstring, delta)
-- function num : 0_1 , upvalues : LrDialogs, lastitem, LrDevelopController
((import("LrApplicationView")).switchToModule)("develop")
if delta == "NILL" then
(LrDialogs.showBezel)(showstring, 1.5)
else
if item ~= lastitem then
  (LrDialogs.showBezel)(showstring, 1.5)
  lastitem = item
end
end
local tool = {loupe = function()
-- function num : 0_1_0 , upvalues : LrDevelopController
(LrDevelopController.selectTool)("loupe")
end
, crop = function()
-- function num : 0_1_1 , upvalues : LrDevelopController
(LrDevelopController.selectTool)("crop")
end
, dust = function()
-- function num : 0_1_2 , upvalues : LrDevelopController
(LrDevelopController.selectTool)("dust")
end
, redeye = function()
-- function num : 0_1_3 , upvalues : LrDevelopController
(LrDevelopController.selectTool)("redeye")
end
, gradient = function()
-- function num : 0_1_4 , upvalues : LrDevelopController
(LrDevelopController.selectTool)("gradient")
end
, circularGradient = function()
-- function num : 0_1_5 , upvalues : LrDevelopController
(LrDevelopController.selectTool)("circularGradient")
end
, localized = function()
-- function num : 0_1_6 , upvalues : LrDevelopController
(LrDevelopController.selectTool)("localized")
end
, upright = function()
-- function num : 0_1_7 , upvalues : LrDevelopController
(LrDevelopController.selectTool)("upright")
end
}
revealOSSpecificPanel(item)
if tool[item] then
(tool[item])()
else
local min, max = (LrDevelopController.getRange)(item)
if min == nil or max == nil then
  return
end
local range = max - min
local operate = (string.sub)(delta, 1, 1)
if operate == "0" then
  (LrDevelopController.resetToDefault)(item)
  value = (LrDevelopController.getValue)(item)
  local handleValue = keepDecimalPlaces(item, value)
  sendMessage(handleValue)
else
  do
	if operate == "+" or operate == "-" then
	  local value = (tonumber((string.sub)(delta, 2, 3)))
	  local step = nil
	  if item == "Exposure" then
		step = 0.02 * value
	  else
		step = range * value / 200
	  end
	  local getValue = (LrDevelopController.getValue)(item)
	  if getValue == nil then
		return
	  end
	  if item == "SplitToningShadowHue" or item == "SplitToningHighlightHue" or item == "ColorGradeMidtoneHue" or item == "ColorGradeGlobalHue" then
		if operate == "+" then
		  if getValue + step > 360 then
			value = getValue + step - 360
		  else
			value = getValue + step
		  end
		else
		  if operate == "-" then
			if getValue - step < 0 then
			  value = getValue + 360 - step
			else
			  value = getValue - step
			end
		  end
		end
		value = GetPreciseDecimal(value, 0)
	  else
		if operate == "+" then
		  value = getValue + step
		else
		  if operate == "-" then
			value = getValue - step
		  end
		end
	  end
	  value = (math.max)(value, min)
	  value = (math.min)(value, max)
	  local handleValue = keepDecimalPlaces(item, value)
	  sendMessage(handleValue)
	  LrDevelopController.setValue(item, value)
	end
  end
end
end
end

changeTemperatureValue = function(item, showstring, delta)
-- function num : 0_2 , upvalues : LrDevelopController, LrDialogs, lastitem
((import("LrApplicationView")).switchToModule)("develop")
local photo = (((import("LrApplication")).activeCatalog)()):getTargetPhoto()
if photo == nil then
return
end
(LrDevelopController.revealPanel)(item)
if delta == "NILL" then
(LrDialogs.showBezel)(showstring, 1.5)
else
if item ~= lastitem then
  (LrDialogs.showBezel)(showstring, 1.5)
  lastitem = item
end
end
local operate = (string.sub)(delta, 1, 1)
if operate == "0" then
(LrDevelopController.resetToDefault)(item)
value = (LrDevelopController.getValue)(item)
local handleValue = keepDecimalPlaces(item, value)
sendMessage(handleValue)
else
do
  if operate == "+" or operate == "-" then
	local value = tonumber((string.sub)(delta, 2, 3))
	local min, max = (LrDevelopController.getRange)(item)
	if min == nil or max == nil then
	  return
	end
	local range = max - min
	local getValue = (LrDevelopController.getValue)(item)
	if getValue == nil then
	  return
	end
	if min < 0 then
	  local step = range * value / 200
	  if operate == "+" then
		value = getValue + step
	  else
		if operate == "-" then
		  value = getValue - step
		end
	  end
	else
	  do
		do
		  local step = (math.log)(max) - (math.log)(min)
		  step = step * (value) / 400
		  if operate == "+" then
			value = (math.exp)((math.log)(getValue) + step)
		  else
			if operate == "-" then
			  value = (math.exp)((math.log)(getValue) - step)
			end
		  end
		  value = (math.max)(value, min)
		  value = (math.min)(value, max)
		  local handleValue = keepDecimalPlaces(item, value)
		  sendMessage(handleValue)
		  LrDevelopController.setValue(item, value)
		end
	  end
	end
  end
end
end
end

ChangeItemInSpecialTool = function(item)
-- function num : 0_3 , upvalues : LrDevelopController, isSDKGreater11
writelog("getSelectedTool:"..item)
local tool = ((LrDevelopController.getSelectedTool)())
local selectedMask, isAdjustLocal = nil, nil
isAdjustLocal = not isSDKGreater11 or tool == "masking"
do
local switch = {Temperature = function()
-- function num : 0_3_0 , upvalues : item
item = "local_Temperature"
end
, Tint = function()
-- function num : 0_3_1 , upvalues : item
item = "local_Tint"
end
, Exposure = function()
-- function num : 0_3_2 , upvalues : item
item = "local_Exposure"
end
, Contrast = function()
-- function num : 0_3_3 , upvalues : item
item = "local_Contrast"
end
, Highlights = function()
-- function num : 0_3_4 , upvalues : item
item = "local_Highlights"
end
, Shadows = function()
-- function num : 0_3_5 , upvalues : item
item = "local_Shadows"
end
, Clarity = function()
-- function num : 0_3_6 , upvalues : item
item = "local_Clarity"
end
, Saturation = function()
-- function num : 0_3_7 , upvalues : item
item = "local_Saturation"
end
, Sharpness = function()
-- function num : 0_3_8 , upvalues : item
item = "local_Sharpness"
end
, LuminanceNoise = function()
-- function num : 0_3_9 , upvalues : item
item = "local_LuminanceNoise"
end
, Moire = function()
-- function num : 0_3_10 , upvalues : item
item = "local_Moire"
end
, Defringe = function()
-- function num : 0_3_11 , upvalues : item
item = "local_Defringe"
end
, Blacks = function()
-- function num : 0_3_12 , upvalues : item
item = "local_Blacks"
end
, Whites = function()
-- function num : 0_3_13 , upvalues : item
item = "local_Whites"
end
, Dehaze = function()
-- function num : 0_3_14 , upvalues : item
item = "local_Dehaze"
end
, Texture = function()
-- function num : 0_3_15 , upvalues : item
item = "local_Texture"
end
, Hue = function()
-- function num : 0_3_16 , upvalues : item
item = "local_Hue"
end
, Amount = function()
-- function num : 0_3_17 , upvalues : item
item = "local_Amount"
end
}
if (tool == "gradient" or tool == "circularGradient" or tool == "localized" or isAdjustLocal) and switch[item] then
  (switch[item])()
end
do return item end
-- DECOMPILER ERROR: 4 unprocessed JMP targets
end
end

handleMessage = function(functionName, functionString, functionParams)
-- function num : 0_4 , upvalues : commandQuerySet, commandResultDic, isTimerStarted
writelog("handleMessage:"..functionName..functionString..functionParams)
if functionName == "getInstructValues" then
if functionParams == "-1" then
  commandQuerySet = {}
  commandResultDic = {}
  isTimerStarted = false
  return
else
  isTimerStarted = true
  (table.insert)(commandQuerySet, functionParams)
end
getInstructValues(functionString, functionParams)
else
if functionName == "getDevelopPresets" then
  foldersPresetsJson = ""
  getDevelopPresets()
else
  if functionName == "applyDevelopPreset" then
	applyDevelopPreset(functionParams)
  else
	if functionParams == "0" then
	  executeFunction(functionName, functionString, functionParams)
	else
	  executeFunction(functionName, functionString, functionParams)
	end
  end
end
end
end

executeFunction = function(functionName, functionString, functionParams)
-- function num : 0_5 , upvalues : isTimerStarted
isTimerStarted = false
functionName = ChangeItemInSpecialTool(functionName)
if functionName == "Temperature" then
changeTemperatureValue(functionName, functionString, functionParams)
else
changeAdjustmentValue(functionName, functionString, functionParams)
end
end

getInstructValues = function(functionString, functionParams)
-- function num : 0_6 , upvalues : commandResultDic
local tableArray = (string.splitToTable)(functionParams, "-")
local resultValues = ""
for k,v in pairs(tableArray) do
if v == "Temperature" then
  resultValues = resultValues .. getTemperatureValue(v) .. "-"
else
  resultValues = resultValues .. getAdjustValue(v) .. "-"
end
end
resultValues = (string.sub)(resultValues, 1, -2)
if resultValues ~= commandResultDic[functionParams] then
sendMessage(resultValues)
-- DECOMPILER ERROR at PC42: Confused about usage of register: R4 in 'UnsetPending'

commandResultDic[functionParams] = resultValues
end
end

getTemperatureValue = function(item)
-- function num : 0_7 , upvalues : LrDevelopController
functionName = ChangeItemInSpecialTool(item)
local photo = (((import("LrApplication")).activeCatalog)()):getTargetPhoto()
if photo == nil then
return
end
local value = (LrDevelopController.getValue)(functionName)
local handleValue = keepDecimalPlaces(item, value)
return handleValue
end

getAdjustValue = function(item)
-- function num : 0_8 , upvalues : LrDevelopController
functionName = ChangeItemInSpecialTool(item)
local value = nil
if functionName == "SplitToningShadowHue" or functionName == "SplitToningHighlightHue" or functionName == "ColorGradeMidtoneHue" or functionName == "ColorGradeGlobalHue" then
value = (LrDevelopController.getValue)(functionName)
if value == nil then
  return
end
value = GetPreciseDecimal(value, 0)
else
value = (LrDevelopController.getValue)(functionName)
end
local handleValue = keepDecimalPlaces(item, value)
return handleValue
end

local saveSenderPort = 0
local saveReceiverPort = 0
local writePortToFile = function(port, index)
-- function num : 0_9 , upvalues : saveSenderPort, saveReceiverPort, LrPathUtils
local portStr = "lrport"
local savePorts = nil
if index == "1" then
saveSenderPort = port
else
saveReceiverPort = port
end
local path = (LrPathUtils.getStandardFilePath)("home")
path = (LrPathUtils.makeAbsolute)(portStr, path)
local portFilePath = (LrPathUtils.child)(_PLUGIN.path, portStr)
if saveSenderPort == 0 and saveReceiverPort == 0 then
savePorts = "0|0"
else
if saveSenderPort ~= 0 and saveReceiverPort ~= 0 then
  savePorts = saveReceiverPort .. "|" .. saveSenderPort
else
  return portFilePath
end
end
local file = (io.open)(portFilePath, "w+")
if file ~= nil then
file:write(savePorts)
file:close()
end
return portFilePath
end

writePresetsToFile = function(jsonString)
-- function num : 0_10 , upvalues : LrPathUtils, LrFileUtils
local osPath = (string.find)(((import("LrSystemInfo")).osVersion)(), "Windows") == nil and "Library/Application Support/ugeeTablet/data" or "\\AppData\\Roaming\\ugeeTablet\\data"
local homeDir = (LrPathUtils.getStandardFilePath)("home")
local targetFolderPath = (LrPathUtils.child)(homeDir, osPath)
LrFileUtils.createAllDirectories(targetFolderPath)
local lrPresetsFilePath = (LrPathUtils.child)(targetFolderPath, "lrPresets")
local file = (io.open)(lrPresetsFilePath, "w+")
if file ~= nil then
file:write(jsonString)
file:close()
end
end

local senderPort = 0
local senderConnected = false
local senderPortFilePath = nil
local senderShutdown = false
local createSenderSocket = function(context)
-- function num : 0_11 , upvalues : LrSocket, senderPort, senderPortFilePath, writePortToFile, senderConnected, senderShutdown, LrDialogs
local sender = (LrSocket.bind)({functionContext = context, port = 0, mode = "send", plugin = _PLUGIN, onConnecting = function(socket, port)
-- function num : 0_11_0 , upvalues : senderPort, senderPortFilePath, writePortToFile
if senderPort ~= port then
  senderPort = port
  senderPortFilePath = writePortToFile(senderPort, "1")
end
end
, onConnected = function(socket, port)
-- function num : 0_11_1 , upvalues : senderConnected
senderConnected = true
end
, onClosed = function(socket)
-- function num : 0_11_2 , upvalues : senderConnected, senderShutdown
senderConnected = false
if senderShutdown then
  socket:reconnect()
end
end
, onError = function(socket, err)
-- function num : 0_11_3 , upvalues : senderShutdown, senderConnected, LrDialogs
if senderShutdown then
  return
end
senderConnected = false
if (string.sub)(err, 1, (string.len)("failed to open")) == "failed to open" then
  (LrDialogs.showError)("Loupedeck needs access to tcp ports, but failed to make a connection.")
  return
end
socket:reconnect()
end
})
return sender
end

sendMessage = function(message)
-- function num : 0_12 , upvalues : lineBreak
if message == nil then
return
end
sender:send(message .. lineBreak)
writelog("send:"..message .. lineBreak)
end

local receiverPort = 0
local receiverConnected = false
local receiverPortFilePath = nil
local receiverShutdown = false
local createReceiverSocket = function(context)
-- function num : 0_13 , upvalues : LrSocket, receiverPort, receiverPortFilePath, writePortToFile, receiverConnected, receiverShutdown, senderConnected, createSenderSocket, LrDialogs, LrTasks
local receiver = (LrSocket.bind)({functionContext = context, port = 0, mode = "receive", plugin = _PLUGIN, onConnecting = function(socket, port)
-- function num : 0_13_0 , upvalues : receiverPort, receiverPortFilePath, writePortToFile
if receiverPort ~= port then
  receiverPort = port
  receiverPortFilePath = writePortToFile(receiverPort, nil)
end
end
, onConnected = function(socket, port)
-- function num : 0_13_1 , upvalues : receiverConnected
receiverConnected = true
end
, onClosed = function(socket)
-- function num : 0_13_2 , upvalues : receiverConnected, receiverShutdown
receiverConnected = false
if receiverShutdown then
  socket:reconnect()
end
end
, onError = function(socket, err)
-- function num : 0_13_3 , upvalues : senderConnected, createSenderSocket, context, receiverShutdown, receiverConnected, LrDialogs
if senderConnected then
  sender = createSenderSocket(context)
end
if receiverShutdown then
  return
end
receiverConnected = false
if (string.sub)(err, 1, (string.len)("failed to open")) == "failed to open" then
  (LrDialogs.showError)("Ugee needs access to tcp ports, but failed to make a connection.")
  return
end
socket:reconnect()
end
, onMessage = function(socket, message)
-- function num : 0_13_4 , upvalues : LrTasks
writelog("receive:"..message)
local functionName, functionString = (string.split)(message, "|")
writelog("canshu1:"..functionName)
local functionParams = nil
functionString,functionParams = (string.split)(functionString, "|")
writelog("canshu2:"..functionString)
writelog("canshu3:"..functionParams)
LrTasks.startAsyncTaskWithoutErrorHandler(function()
  -- function num : 0_13_4_0 , upvalues : functionName, functionString, functionParams
  handleMessage(functionName, functionString, functionParams)
end
, "handleMessage")
end
})
return receiver
end

(LrTasks.startAsyncTask)(function()
-- function num : 0_14 , upvalues : LrFunctionContext, createSenderSocket, createReceiverSocket, LrTasks, receiverShutdown, senderShutdown, receiverPortFilePath, writePortToFile, senderPortFilePath, receiverConnected, senderConnected
(LrFunctionContext.callWithContext)("Ugee", function(context)
-- function num : 0_14_0 , upvalues : createSenderSocket, createReceiverSocket, LrTasks, receiverShutdown, senderShutdown, receiverPortFilePath, writePortToFile, senderPortFilePath, receiverConnected, senderConnected
sender = createSenderSocket(context)
local receiver = createReceiverSocket(context)
-- DECOMPILER ERROR at PC8: Confused about usage of register: R2 in 'UnsetPending'
writelog("Ugee init:")
plugin.running = true
while plugin.running do
  (LrTasks.sleep)(0.25)
end
getDevelopPresets()
receiverShutdown = true
senderShutdown = true
receiverPortFilePath = writePortToFile(0, nil)
senderPortFilePath = writePortToFile(0, "1")
if receiverConnected then
  receiver:close()
end
if senderConnected then
  sender:close()
end
-- DECOMPILER ERROR at PC46: Confused about usage of register: R2 in 'UnsetPending'

plugin.shutdown = true
end
)
end
)
local currentModuleName = ""
(LrTasks.startAsyncTask)(function()
-- function num : 0_15 , upvalues : LrFunctionContext, LrTasks, isTimerStarted, commandQuerySet, currentModuleName, LrApplicationView
(LrFunctionContext.callWithContext)("Timer", function(context)
-- function num : 0_15_0 , upvalues : LrTasks, isTimerStarted, commandQuerySet, currentModuleName, LrApplicationView
while 1 do
  while 1 do
	if plugin.running then
	  (LrTasks.sleep)(0.5)
	  if isTimerStarted then
		writelog("Ugee Timer:")
		for key,value in pairs(commandQuerySet) do
		  currentModuleName = (LrApplicationView.getCurrentModuleName)()
		  if currentModuleName == "develop" then
			getInstructValues(functionString, value)
		  else
			(LrTasks.sleep)(0.5)
			break
		  end
		end
		-- DECOMPILER ERROR at PC34: LeaveBlock: unexpected jumping out IF_THEN_STMT

		-- DECOMPILER ERROR at PC34: LeaveBlock: unexpected jumping out IF_STMT

		-- DECOMPILER ERROR at PC34: LeaveBlock: unexpected jumping out IF_THEN_STMT

		-- DECOMPILER ERROR at PC34: LeaveBlock: unexpected jumping out IF_STMT

	  end
	end
  end
  (LrTasks.sleep)(0.75)
  isTimerStarted = true
end
end
)
end
)
local escapeSpecialChars = function(str)
-- function num : 0_16
local escapeTable = {["\""] = "\\\"", ["\\"] = "\\\\", ["/"] = "\\/", ["\b"] = "\\b", ["\f"] = "\\f", ["\n"] = "\\n", ["\r"] = "\\r", ["\t"] = "\\t"}
return str:gsub("[\\\"\\/\\b\\f\\n\\r\\t]", escapeTable)
end

local jsonEncode = function(data)
-- function num : 0_17 , upvalues : escapeSpecialChars
local jsonString = "{\"presetFolders\":["
local isFirstFolder = true
for _,folder in ipairs(data.presetFolders) do
if not isFirstFolder then
  jsonString = jsonString .. ","
else
  isFirstFolder = false
end
jsonString = jsonString .. "{\"folderName\":\"" .. escapeSpecialChars(folder.folderName) .. "\",\"presetList\":["
local isFirstPreset = true
for _,preset in ipairs(folder.presetList) do
  if not isFirstPreset then
	jsonString = jsonString .. ","
  else
	isFirstPreset = false
  end
  jsonString = jsonString .. "{\"presetName\":\"" .. escapeSpecialChars(preset.presetName) .. "\",\"presetUuid\":\"" .. escapeSpecialChars(preset.presetUuid) .. "\"}"
end
jsonString = jsonString .. "]}"
end
jsonString = jsonString .. "]}"
return jsonString
end

local presetSeparator = "@"
local presetReplace = "-"
getDevelopPresetFolders = function()
-- function num : 0_18 , upvalues : LrApplication, presetReplace
local presetResult = ""
local presetFolders = (LrApplication.developPresetFolders)()
for _,folder in pairs(presetFolders) do
presetResult = presetResult .. "|" .. (string.gsub)(folder:getName(), "|", presetReplace)
end
return presetResult
end

local cachePresetsTable = {}
do
local currentPresetsTable = {}
getDevelopPresets = function()
-- function num : 0_19 , upvalues : LrApplication, presetReplace, currentPresetsTable, jsonEncode, cachePresetsTable
local presetData = {
presetFolders = {}
}
local presetFolders = (LrApplication.developPresetFolders)()
for _,folder in pairs(presetFolders) do
local folderName = (string.gsub)(folder:getName(), "|", presetReplace)
local newFolder = {folderName = folderName,
presetList = {}
}
local presets = folder:getDevelopPresets()
for _,preset in pairs(presets) do
  local presetName = (string.gsub)(preset:getName(), "|", presetReplace)
  local presetUuid = preset:getUuid()
  local newPreset = {presetName = presetName, presetUuid = presetUuid}
  (table.insert)(newFolder.presetList, newPreset)
  -- DECOMPILER ERROR at PC45: Confused about usage of register: R18 in 'UnsetPending'

  currentPresetsTable[presetName] = presetUuid
end
(table.insert)(presetData.presetFolders, newFolder)
end
local jsonString = jsonEncode(presetData)
if foldersPresetsJson ~= jsonString then
foldersPresetsJson = jsonString
cachePresetsTable = currentPresetsTable
writePresetsToFile(foldersPresetsJson)
end
return jsonString
end

foldersPresetsJson = getDevelopPresets()
applyDevelopPreset = function(presetNameAndUuid)
-- function num : 0_20 , upvalues : LrApplication, cachePresetsTable, LrTasks, LrDialogs
local presetName, presetUuid = (string.match)(presetNameAndUuid, "(.-)&(.+)")
local preset = (LrApplication.developPresetByUuid)(presetUuid)
do
if preset == nil then
  local newUuid = cachePresetsTable[presetName]
  if newUuid ~= nil then
	preset = (LrApplication.developPresetByUuid)(newUuid)
  end
end
if preset == nil then
  return
end
local presetName = preset:getName() .. " preset"
if isApplyingPreset then
  return
end
isApplyingPreset = true
(LrTasks.startAsyncTask)(function()
-- function num : 0_20_0 , upvalues : LrApplication, LrTasks, presetName, preset, LrDialogs
local catalog = (LrApplication.activeCatalog)()
local success, errorMessage = (LrTasks.pcall)(function()
  -- function num : 0_20_0_0 , upvalues : catalog, presetName, preset
  catalog:withWriteAccessDo(presetName, function(context)
	-- function num : 0_20_0_0_0 , upvalues : catalog, preset
	local photos = catalog:getTargetPhotos()
	for _,photo in ipairs(photos) do
	  if photo ~= nil then
		photo:applyDevelopPreset(preset)
	  end
	end
	showBezel(preset:getName())
  end
)
end
)
isApplyingPreset = false
if not success then
  (LrDialogs.message)("Error applying preset: " .. errorMessage)
end
end
)
end
end

-- DECOMPILER ERROR: 1 unprocessed JMP targets
end



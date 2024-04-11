plugin = 
{
name = "Ugee", 
version = {major = 1, minor = 0, revision = 1, build = 202404}, 
loggingMode = "", 
running = false, 
shutdown = false, 
prefs = ((import("LrPrefs")).prefsForPlugin)()
}

local LrLogger = import("LrLogger")
local myLogger = LrLogger("TWExportLogger")
isDebug = false
myLogger:enable("logfile")
outputToLog = function(format, ...)
  -- function num : 0_0 , upvalues : myLogger
  if isDebug then
    myLogger:trace(format, ...)
  end
end

showBezel = function(message)
  -- function num : 0_1
  if (plugin.prefs).showBezel then
    ((import("LrDialogs")).showBezel)(message)
  end
end

function writelog(log)
  local logpath = import("LrPathUtils").child(_PLUGIN.path, "ugeelogs")--将路径元素组合成单个路径
  local r6_36 = io.open(logpath, "a+")
  if r6_36 ~= nil then
    r6_36:write(log)
    r6_36:close()
  end
end
-- DECOMPILER ERROR at PC36: Confused about usage of register: R2 in 'UnsetPending'

string.startsWith = function(text, startText)
  -- function num : 0_2
  do return (string.sub)(text, 1, (text.len)(startText)) == startText end
  -- DECOMPILER ERROR: 1 unprocessed JMP targets
end

-- DECOMPILER ERROR at PC39: Confused about usage of register: R2 in 'UnsetPending'
--[[
string.split = function(text, separator)
  -- function num : 0_3
  local separator1, separator2 = (string.find)(text, separator, 1, true)
  local part1 = nil
  if separator1 ~= nil or not text then
    part1 = (string.sub)(text, 1, separator1 - 1)
  end
  if separator1 == nil then
    local part2 = (string.sub)(text, separator2 + 1)
    return part1, part2
  end
end
--]]
function string.split(r0_4, r1_4)
  -- line: [53, 61] id: 4
  local r2_4, r3_4 = string.find(r0_4, r1_4, 1, true)
  local r4_4 = nil	-- notice: implicit variable refs by block#[4]
  if r2_4 == nil then
    r4_4 = r0_4
    if r4_4 then
      --::label_11::
      r4_4 = string.sub(r0_4, 1, r2_4 - 1)
    end
  else
	r4_4 = string.sub(r0_4, 1, r2_4 - 1)
    --goto label_11	-- block#2 is visited secondly
  end
  if r2_4 == nil then
  end
  return r4_4, string.sub(r0_4, r3_4 + 1)
end
-- DECOMPILER ERROR at PC42: Confused about usage of register: R2 in 'UnsetPending'

string.splitToTable = function(str, reps)
  -- function num : 0_4
  local resultStrList = {}
  --;
  (string.gsub)(str, "[^" .. reps .. "]+", 
  function(w)
    -- function num : 0_4_0 , upvalues : resultStrList
    (table.insert)(resultStrList, w)
  end
)
  return resultStrList
end

shutdownPlugin = function()
  -- function num : 0_5
  -- DECOMPILER ERROR at PC5: Confused about usage of register: R0 in 'UnsetPending'

  if plugin.running then
    plugin.shutdown = false
    -- DECOMPILER ERROR at PC7: Confused about usage of register: R0 in 'UnsetPending'

    plugin.running = false
  end
end

keepDecimalPlaces = function(CommandName, realValue)
  -- function num : 0_6
  realValue = HandleNullValue(realValue)
  CommandName = (string.gsub)(CommandName, "local_", "")
  if CommandName == "Exposure" or CommandName == "straightenAngle" then
    return CommandName .. "=" .. roundedDecimal(realValue, 2)
  else
    if CommandName == "SharpenRadius" or CommandName == "PerspectiveRotate" or CommandName == "PerspectiveX" or CommandName == "PerspectiveY" or CommandName == "Hue" then
      return CommandName .. "=" .. roundedDecimal(realValue, 1)
    else
      if CommandName == "GrainAmount" then
        return CommandName .. "=" .. (math.ceil)(realValue)
      else
        return CommandName .. "=" .. roundedDecimal(realValue, 0)
      end
    end
  end
end

roundedDecimal = function(realValue, number)
  -- function num : 0_7
  return (string.format)("%." .. number .. "f", realValue)
end

floorDecimal = function(realValue, number)
  -- function num : 0_8
  return realValue - realValue % (1 / 10 ^ number)
end

HandleNullValue = function(currentValue)
  -- function num : 0_9
  if currentValue == nil then
    return 0
  else
    return currentValue
  end
end



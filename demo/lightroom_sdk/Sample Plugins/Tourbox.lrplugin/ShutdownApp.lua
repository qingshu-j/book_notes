require("Globals")
local shutdownFunction = function(doneFunction, progressFunction)
  -- function num : 0_0
  progressFunction(0, "Shutdown started")
  shutdownPlugin()
  progressFunction(1, "Shutdown finished")
  doneFunction()
end

return {LrShutdownFunction = shutdownFunction}


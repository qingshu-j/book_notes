require("Globals")
local header = (string.format)("Ugee version %d.%d.%d.%d", (plugin.version).major, (plugin.version).minor, (plugin.version).revision, (plugin.version).build)
local message = (string.format)("Copyright © %d Hanvon Ugee Technology Co., Ltd. All rights reserved. https://www.ugee.com.cn/.", ((os.date)("*t")).year)
import("LrDialogs").message(header,message,"info")
--((import("LrDialogs")).message)(header, message, "info")


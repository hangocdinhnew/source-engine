local dap = require("dap")

dap.adapters.lldb = {
	type = "executable",
	command = "/usr/bin/lldb-vscode",
	name = "lldb",
}

dap.configurations.cpp = {
	{
		name = "hl2_test",
		type = "lldb",
		request = "launch",
		program = "/home/hangocdinh/Downloads/Compressed/HL2/hl2_launcher",
		cwd = "/home/hangocdinh/Downloads/Compressed/HL2",
		stopOnEntry = false,
		args = { "-allowdebug", "-sw", "-condebug", "-console", "-toconsole", "-fullscreen", "-h 1920", "-w 1820" },
	},
}

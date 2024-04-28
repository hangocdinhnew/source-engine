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
		program = "~/Downloads/Compressed/HL2/hl2_launcher",
		cwd = "${workspaceFolder}",
		stopOnEntry = false,
		args = {},
	},
}

sptbl["reverse"] = {

	files = {
	    module = "reverse.c",
	    header = "reverse.h",
	    example = "ex_reverse.c",
	},

	func = {
	    create = "ut_reverse_create",
	    destroy = "ut_reverse_destroy",
	    init = "ut_reverse_init",
	    compute = "ut_reverse_compute",
	},

	params = {
	    mandatory = {
	        {
	            name = "delay",
	            type = "UTFLOAT",
	            description = "Delay time in seconds.",
	            default = "1.0"
	        }
	    }
	},

	modtype = "module",

	description = [[Signal reverser

	Reverse will store a signal inside a buffer and play it back reversed.]],

	ninputs = 1,
	noutputs = 1,

	inputs = {
	    {
	        name = "input",
	        description = "Signal input."
	    }
	},

	outputs = {
	    {
	        name = "out",
	        description = "Signal output."
	    }
	}

}

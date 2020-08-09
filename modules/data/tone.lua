sptbl["tone"] = {

	files = {
	    module = "tone.c",
	    header = "tone.h",
	    example = "ex_tone.c",
	},

	func = {
	    create = "ut_tone_create",
	    destroy = "ut_tone_destroy",
	    init = "ut_tone_init",
	    compute = "ut_tone_compute",
	},

	params = {
	    optional = {
	        {
	            name = "hp",
	            type = "UTFLOAT",
	            description = "The response curve's half power point (aka cutoff frequency).",
	            default = "1000"
	        },
	    },
	},

	modtype = "module",

	description = [[First-order recursive lowpass filter]],

	ninputs = 1,
	noutputs = 1,

	inputs = {
	    {
	        name = "in",
	        description = "Signal input."
	    },
	},

	outputs = {
	    {
	        name = "out",
	        description = "Signal Output."
	    },
	}

}

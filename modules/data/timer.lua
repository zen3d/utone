sptbl["timer"] = {

    files = {
        module = "timer.c",
        header = "timer.h",
        example = "ex_timer.c",
    },

    func = {
        create = "ut_timer_create",
        destroy = "ut_timer_destroy",
        init = "ut_timer_init",
        compute = "ut_timer_compute",
    },

    params = {
    },

    modtype = "module",

    description = [[Tap-tempo like timer

When triggered, timer will begin an internal stopwatch until it is triggered again.
The output of the timer will be the time elapsed in seconds.
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "clock",
            description = "When non-zero, will start/stop the timer."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Outputs the time of the last timer (in seconds)."
        },
    }

}

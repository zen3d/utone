sptbl["voc"] = {

    files = {
        module = "voc.c",
        header = "voc.h",
        example = "ex_voc.c",
    },

    func = {
        create = "ut_voc_create",
        destroy = "ut_voc_destroy",
        init = "ut_voc_init",
        compute = "ut_voc_compute",
    },

    params = {
    },

    modtype = "module",

    description = [[A vocal tract physical model.

Based on the Pink Trombone algorithm by Neil Thapen, Voc implements a physical 
model of the vocal tract glottal pulse wave. The tract model is based on the 
classic Kelly-Lochbaum
segmented cylindrical 1d waveguide model, and the glottal pulse wave is a
LF glottal pulse model. 

The utone source code for Voc is generated via ctangle, one half of the
literate documentation system known CWEB. The CWEB are maintained in a 
separate repository. They are hosted on github here: 
http://www.github.com/paulbatchelor/voc

This documentation is a stub. For a full overview on proper usage, consult
the "Top-level functions" section of the documented code, a copy of which
can be found at the Voc project page pbat.ch/proj/voc, or generate the PDF
from the github page described above.
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Voc output."
        },
    }

}

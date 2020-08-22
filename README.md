# cookiecutter-dpf-faust

A [cookiecutter] project template for DISTRHO Plugin Framework ([DPF]) audio
effect plugins using [FAUST] for the implementation of the DSP pipeline.

[![quickstart asciicast](https://asciinema.org/a/355004.svg)](https://asciinema.org/a/355004?speed=2&&theme=monokai&autoplay=1&size=medium)

## Quickstart

To create a DPF effect plugin using this template, install cookiecutter (see
the [installation instructions]) and then run:

```console
$ cookiecutter https://github.com/SpotlightKid/cookiecutter-dpf-faust
```

and enter the plugin name and other info at the prompts. (See the
[cookiecutter documentation] on how to change the default values for these
prompts.)

Here is an example (some output omitted for clarity):

```console
$ cookiecutter https://github.com/SpotlightKid/cookiecutter-dpf-faust
project_name [DPF FAUST Gain]:
plugin_description [A simple audio volume gain plugin]:
author_name [Joe Doe]: Christopher Arndt
domain [example.com]: chrisarndt.de
github_username [christopher.arndt]: SpotlightKid
email [SpotlightKid@chrisarndt.de]: info@chrisarndt.de
plugin_brand [chrisarndt.de]:
plugin_name [DPFFAUSTGain]: DpfFaustGain
repo_name [dpffaustgain]:
plugin_uri [https://chrisarndt.de/plugins/dpffaustgain]:
project_license [MIT]:
version [0.1.0]:
year [2020]:
num_inputs [1]:
num_outputs [1]:

Running post-project-generation hook...

Initializing new Git repository:
Leeres Git-Repository in /home/chris/dpffaustgain/.git/ initialisiert
Adding Git submodule for DPF library:
Checking out submodules:
Klone nach '/home/chris/dpffaustgain/dpf' ...
[...]
Making initial Git commit:
[master (Root-Commit) 88d8ec2] Initial commit
 17 files changed, 1291 insertions(+)
[...]

Your DPF/FAUST audio effect plugin project is now ready!
To compile it, change into the 'dpffaustgain' directory and type 'make'.
The plugin binaries and LV2 bundle will be placed in the 'bin' subdirectory.
Have fun!
```

A directory named after the value you gave for `repo_name` will be created
and initialized as a Git repository and DPF added as a Git submodule.

Enter the directory and run `make`:

```console
$ cd dpffaustgain
$ make
```

The resulting plugin binaries will be placed in the `bin` sub-directory of your
project.

The FAUST DSP implementation will be in in the `faust` sub-directory, in a file
named `<plugin_name>.dsp` (in all lower-case). Adapt it as you see fit and run
`make` again to re-generate the C++ source code from the the FAUST source and
to rebuild the binaries. The second compilation will be much faster, because
the DPF library has already been built.

The static and generated source code for your plugin is in a sub-directory of
the `plugins` directory named after the value you specified for `plugin_name`
(again in all lower-case).

See the `README.md` file in your generated project for more information on
compiling, prerequisites and how to install the finished plugin(s).


## Requirements

To create a project using this cookie cutter template you need:

* Python
* Git
* [cookiecutter]

To build the generated project, you need additional development tools. See the
`README.md` file in your generated project for more information.


## License

This cookiecutter template is released under MIT license. See the
[LICENSE](./LICENSE) file for more information.

When generating a project using this template, you may choose any license you
like for the resulting files.

`faustpp` architecture files in the `faust/arch` directory of generated
projects are distributed under the Boost Software License 1.0 and come with a
special license exception, which can be found in the `LICENSE-EXCEPTION.md`
file in the same dierctory.


## Authors

* Christopher Arndt (@SpotlightKid)
* Jean Pierre Cimalando (@jpcima) - [faustpp] architecture files


[cookiecutter]: https://github.com/cookiecutter/cookiecutter
[cookiecutter documentation]: https://cookiecutter.readthedocs.io/en/latest/advanced/user_config.html
[DPF]: https://github.com/DISTRHO/DPF
[installation instructions]: http://cookiecutter.readthedocs.org/en/latest/installation.html
[FAUST]: https://faust.grame.fr/
[faustpp]: https://github.com/jpcima/faustpp.git

# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

include(ComponentUtils)

initialize_components()

register_component_auto(common)
register_component_auto(file_container)
register_component_auto(fonts)
register_component_auto(imaging)
register_component_auto(logger)
register_component_auto(math)
register_component_auto(midi)
register_component_auto(mono)
register_component_auto(plugins)
register_component_auto(ptree)
register_component_auto(reflection)
register_component_auto(reflection_support)
register_component_auto(rdp)
register_component_auto(serial)
register_component_auto(sockets)
register_component_auto(streams)
register_component_auto(testing)
register_component_auto(tracelog)
register_component_auto(unicode)
register_component_auto(web)

finalize_components()

set(PLANTUML_JARFILE "" CACHE FILEPATH "plantuml.jar file path")
set(plantuml java -jar ${PLANTUML_JARFILE})

# Example how to create custom function to generate plant uml for each directories
# function(add_diagram target source_path)

#   set(plantuml java -jar ${PLANTUML_JARFILE})
#   get_filename_component(output ${source_path} NAME_WE)

#   add_custom_target(${target} ALL)
#   add_custom_command(TARGET ${target}
#     COMMAND
#       ${plantuml} ${source_path}/*.uml
#     COMMENT
#       "Rendering diagram '${source_path}'."
#   )

# endfunction()

# add_diagram(UML_DomainModelDiagrams
#   ${CMAKE_SOURCE_DIR}/docs/design/01-DomainModelDiagrams)

# add_diagram(UML_UseCaseDiagrams
#   ${CMAKE_SOURCE_DIR}/docs/design/02-UseCaseDiagrams)

# add_custom_target(UML DEPENDS
#   UML_DomainModelDiagrams
#   UML_UseCaseDiagrams)

add_custom_target(UML)
add_custom_command(TARGET UML
  COMMAND ${plantuml} ${CMAKE_SOURCE_DIR}/docs/design/*/*.uml)

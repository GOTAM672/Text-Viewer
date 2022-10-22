text_viewer_sources = [
  'main.c',
  'text-viewer-application.c',
  'text-viewer-window.c',
]

text_viewer_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1'),
]

text_viewer_sources += gnome.compile_resources('text-viewer-resources',
  'text-viewer.gresource.xml',
  c_name: 'text_viewer'
)

executable('text-viewer', text_viewer_sources,
  dependencies: text_viewer_deps,
       install: true,
)

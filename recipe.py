from build import Build
from build import BinaryType as Binfmt

b = Build("catpak")

b.add_compiler_arguments([
  "-Wall", "-Wextra", "-Wpedantic", "-std=gnu23", "-ggdb3"
])

b.add_file(["src/main.c"], ["catpak_search.o", "catpak_init.o"], Binfmt.Program)
b.add_file(["src/catpak_search.c"], None, Binfmt.Object)
b.add_file(["src/catpak_init.c"], None, Binfmt.Object)

b.start_build()
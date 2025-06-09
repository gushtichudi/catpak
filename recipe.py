from build import Build
from build import BinaryType as Binfmt

b = Build("catpak")

b.override_default_compiler("gcc")

b.add_compiler_arguments([
  "-Wall", "-Wextra", "-Wpedantic", "-std=gnu23", "-ggdb3", "-march=native"
])

b.add_file(
  ["src/main.c"], 
  ["catpak_search.o", "catpak_init.o", "catpak_transaction_main.o"], 
  Binfmt.Program
  )
  
b.add_file(["src/catpak_search.c"], None, Binfmt.Object)
b.add_file(["src/catpak_init.c"], None, Binfmt.Object)
b.add_file(["src/catpak_transaction_main.c"], None, Binfmt.Object)

b.start_build()
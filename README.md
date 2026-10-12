# code_bits

> *"Small enough to finish, big enough to deserve its own Makefile."*

Because apparently one folder for "random stuff I built while avoiding real work" wasn't enough.

This is a growing collection of small, self-contained coding projects — *bits*, if you will. Each one lives
in its own subfolder, brings its own `Makefile`, and is stubbornly independent from the rest. No monorepo
build system, no shared CI, no drama. Just code that does a thing, and a `make run` that shows you the thing.

## The Family Photo So Far

| Folder          | What it is                                                                          |
| --------------- | ----------------------------------------------------------------------------------- |
| `hyper_log_log` | Counts unique words in a book. Twice. Once exactly, once with statistics and vibes. |

More folders will show up whenever the author has a new shower thought. The table above is not a promise
of scope; it's a progress report.

## The Ritual (a.k.a. How to Run Anything Here)

Every subfolder follows the same convention. From inside a project directory:

```bash
make clean      # wipe the build folder, like it never happened
make generate   # configure/build system (CMake), generate build files
make run        # build if needed, then run the executable
```

There are extra goodies hiding in the `Makefile` too, if you're curious:

| Command             | Does                                                            |
| ------------------- | --------------------------------------------------------------- |
| `make` / `make all` | Same as `make run`. Convenience wins.                           |
| `make build`        | Compile without running. For the patient.                       |
| `make run_only`     | Run the existing binary, no rebuilding. For the impatient.      |
| `make help`         | Reminds you of the commands you already forgot.                 |
| `make clean`        | Deletes the build products. The "undo" button for `make build`. |

Under the hood the toolchain is CMake + Ninja (`-G "Ninja"`, `Debug`), so make sure you have
`cmake` and `ninja` installed. If you don't, `make generate` will complain loudly and with confidence.

---

## `hyper_log_log`

> *"Why count words exactly when you can count them approximately, faster, and smugly?"*

The flagship bit. Give it a big text file (Project Gutenberg classics, in this case), and it tells you
how many unique words are in it — using two very different philosophies:

1. **`SetCounter`** — the honest one. Dumps every word into an `std::unordered_set` and counts the keys.
   Exact, boring, and slowly eats your RAM.
2. **`HyperLogLogCounter<16>`** — the clever one. Hashes each word, throws it into one of 2¹⁶ buckets,
   remembers only the length of the longest run of leading zeros it saw, and then *guesses* the cardinality
   from a harmonic mean. It uses a fixed amount of memory no matter how large the input is, and in exchange
   it is approximately right. Emphasis on *approximately*.

The output is basically a measurable act of hubris:

```
Unique words:
a) Set: <the true number>
b) HLL: <a number that is suspiciously close>
```

Because both counters implement `UniqueWordCounterInterface`, the same `FileParser` feeds both without
knowing or caring which one it's talking to. Polymorphism, but for word counting.

The sample inputs (Dracula, Moby Dick, Pride and Prejudice) live under `input/`. Pick your poison by editing
the `text_path` in `source/main/main.cpp` — the current favorite is `moby_dick.txt`.

### Build & run

```bash
cd hyper_log_log
make run
```

### Neovim creature comforts

There's a `lua/init.lua` in there for people whose editor is also their personality. It wires up
`<leader>nc / <leader>ng / <leader>nb / <leader>nr` to the `make` commands and registers a
codeLLDB debug configuration, so you can step through the 2¹⁶ buckets line by line at 2 a.m.

---

## Adding a New Bit

1. Make a folder.
2. Give it a `Makefile` with `clean`, `generate`, and `run`.
3. Try not to overthink it.

That's the whole contribution guide. It's short because there's nobody to argue with.

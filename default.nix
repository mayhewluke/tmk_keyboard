{ nixpkgs ? import <nixpkgs> {}, keyboard ? "ergodox" }:

with nixpkgs;
with pkgs;

let
  loader = "${teensy-loader-cli}/bin/teensy-loader-cli";
  subdir = "keyboard/${keyboard}";
  make   = "make $makeFlags -f $makefile --no-print-directory";
  script = "make-teensy";
in
  stdenv.mkDerivation rec {
    name = "tmk-keyboard-${keyboard}";
    src = ./.;
    buildInputs = [ avrgcclibc ];
    makefile = "Makefile.lufa";
    makeFlags = "-C ${subdir}";
    installPhase = ''
      mkdir -p $out

      pushd ${subdir} && make -f ${makefile} clean && popd
      # Copy build results
      ${make} program PROGRAM_CMD="cp -p \$^ $out/"

      # Put teensy target commands into a script
      cat >$out/${script} <<EOF
      #!/bin/sh
      cd $out
      exec $(${make} -n teensy | sed 's@teensy_loader_cli@${loader}@g')
      EOF
      chmod a+x $out/${script}
    '';
  }

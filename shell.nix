with import <nixpkgs> {};
mkShell {
  nativeBuildInputs = with pkgs; [
		clang-tools
		libllvm
		valgrind
	];
	buildInputs = with pkgs; [
    libbsd
		xorg.libX11
		xorg.libXext
	];
	shellHook =
	''
		export LIBX11_PATH="${pkgs.xorg.libX11}"
	'';
}

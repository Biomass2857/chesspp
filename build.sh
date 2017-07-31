#!/bin/bash
# ver: 1.0.3 release

filename="exe"
useC=false
useCPP=true
cc_flags=""
lc_flags=""
ccpp_flags="-D_GLIBCXX_USE_CXX11_ABI=0"
lcpp_flags=""

# SFML

useSFML=true
sfml_version="2.4.2"
sfml_path="/home/siphalor/Documents/"
csfml_flags=""
lsfml_flags="-lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-network"

# SFML


# Select Compiler

if [ "$#" -gt 0 ] && [ "$1" == "cleanup" ];
then
	{
		rm "$filename"
		rm *.o
		rm *.gch
	} &>/dev/null
else
	if [ "$useC" = true ] && [ "$useCPP" = true ] || [ "$useCPP" = true ];
	then
		GXX="/usr/bin/g++"
	elif [ "$useC" = true ] && [ "$useCPP" = false ];
	then
		GXX="/usr/bin/gcc"
	fi

	# Select Compiler end

	# cleanup

	{
		rm "$filename"
		rm *.o
		rm *.gch
	} &>/dev/null

	# cleanup end

	# compilation start

	cfiles=()
	hfiles=()
	cppfiles=()
	hppfiles=()

	{
		cfiles="$(ls *.c)"
		hfiles="$(ls *.h)"
		cppfiles="$(ls *.cpp)"
		hppfiles="$(ls *.hpp)"
	} &>/dev/null

	filez=()
	if [ "$useC" = true ] && [ "$useCPP" = true ];
	then
		if [ "${#cfiles[*]}" -gt 0 ] && [ "${cfiles[0]}" != "" ];
		then
			filez+=('*.c')
		fi
		if [ "${#hfiles[*]}" -gt 0 ] && [ "${hfiles[0]}" != "" ];
		then
			filez+=('*.h')
		fi
		if [ "${#cppfiles[*]}" -gt 0 ] && [ "${cppfiles[0]}" != "" ];
		then
			filez+=('*.cpp')
		fi
		if [ "${#hppfiles[*]}" -gt 0 ] && [ "${hppfiles[0]}" != "" ];
		then
			filez+=('*.hpp')
		fi
	elif [ "$useCPP" = true ];
	then
		if [ "${#cppfiles[*]}" -gt 0 ] && [ "${cppfiles[0]}" != "" ];
		then
			filez+=('*.cpp')
		fi
		if [ "${#hppfiles[*]}" -gt 0 ] && [ "${hppfiles[0]}" != "" ];
		then
			filez+=('*.hpp')
		fi
	elif [ "$useC" = true ];
	then
		if [ "${#cfiles[*]}" -gt 0 ] && [ "${cfiles[0]}" != "" ];
		then
			filez+=('*.c')
		fi
		if [ "${#hfiles[*]}" -gt 0 ] && [ "${hfiles[0]}" != "" ];
		then
			filez+=('*.h')
		fi
	fi

	if [ "$useSFML" = true ] && [ "$useCPP" = true ];
	then
		exec="$($GXX ${filez[*]} -c -I$sfml_path/SFML-$sfml_version/include $ccpp_flags $csfml_flags)"
	elif [ "$useCPP" = true ];
	then
		exec="$($GXX ${filez[*]} -c $ccpp_flags)"
	elif [ "$useC" = true ];
	then
		exec="$($GXX ${filez[*]} -c $cc_flags)"
	fi

	# compilation end

	# linking start

	{
		ofiles="$(ls *.o)"
	} &>/dev/null

	if [ "$useCPP" = true ];
	then
		if [ "$useSFML" = true ];
		then
			exec="$($GXX ${ofiles[*]} -o $filename -L$sfml_path/SFML-$sfml_version/lib $lcpp_flags $lsfml_flags)"
		else
			exec="$($GXX ${ofiles[*]} -o $filename $lcpp_flags)"
		fi
	elif [ "$useC" = true ];
	then
		exec="$($GXX ${ofiles[*]} -o $filename $lc_flags)"
	fi

	# linking end

	# execute start

	if [ -a "$filename" ];
	then
		echo "[INFO] Build successful"
		./"$filename"
	fi

	# execute end
fi

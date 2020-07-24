export CLEO3DEF_SILENT=1
DEFAULT_SRC=$HOME/src
DEFAULT_REL=20050316_FULL

# cleo_init [ source_path [ release [ build_path ] ] ]
function cleo_init () { 
   function abspath () { echo $1 | awk '/^\// {print } ; /^[^\/]/ {print "'`pawd`'/"$0}'; }
   local USER_REL

   USER_SRC=`abspath ${1:-$DEFAULT_SRC}`
   USER_REL=${2:-$DEFAULT_REL}
   USER_BUILD=`abspath ${3:-"/cdat/tem/$USER/$USER_REL/"}`

   if ! [ -d $USER_BUILD ] ; then
      mkdir -p $USER_BUILD
   fi
   
   export USER_SRC
   export USER_BUILD
   export USER_SHLIB=$USER_BUILD/`uname`/shlib ;
   . /nfs/cleo3/Offline/scripts/cleo3logins &>/dev/null
   . /nfs/cleo3/Offline/scripts/cleo3defs &>/dev/null
   c3rel $USER_REL ;
   export PATH=$PATH:$ROOTSYS/bin
};


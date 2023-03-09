#set ARGS=($_)
#echo "ARGS "${ARGS}
setenv SCRIPT_COM `echo $_ | awk '{print $NF}'`
#echo "COM "${SCRIPT_COM}
setenv SCRIPT_DIR `dirname ${SCRIPT_COM}`
#echo "DIR "${SCRIPT_DIR}
setenv SCRIPT_TOP `dirname ${SCRIPT_DIR}`
#echo "TOP "${SCRIPT_TOP}
setenv OLD_ROOTSYS `printenv | awk -F= '($1=="ROOTSYS"){print $2}'`
#if { ${ROOTSYS_OLD} == "" } then
#  setenv ROOTSYS_OLD root
#end

#if ( "---"${OLD_ROOTSYS}"+++" == "---+++" ) then
#  setenv OLD_ROOTSYS_COM `which root`
#  if ( "---"${OLD_ROOTSYS_COM}"+++" != "---+++" ) then
#    setenv OLD_ROOTSYS `dirname ${OLD_ROOTSYS_COM}`
#  endif
#endif

setenv ROOTSYS `${SCRIPT_DIR}/getAbsPath.sh ${SCRIPT_TOP}`

setenv OLD_PATH ${PATH}
setenv PATH `printenv | awk -F= '($1=="OLD_PATH"){print $2}' | awk -F: '{for(i=1;i<=NF;++i)print $i}' | awk -v OLD_ROOTSYS="${OLD_ROOTSYS}" 'BEGIN{c=0} {if((match($0,OLD_ROOTSYS)==0)||(OLD_ROOTSYS=="")){if(c==1)printf(":"); printf($0); c=1}} END{print ""}'`
if ( "---"${PATH}"+++" != "---+++" ) then
  setenv PATH ${PATH}":"
endif
setenv PATH ${PATH}${ROOTSYS}"/bin"

setenv OLD_LD_LIBRARY_PATH ${LD_LIBRARY_PATH}
setenv LD_LIBRARY_PATH `printenv | awk -F= '($1=="OLD_LD_LIBRARY_PATH"){print $2}' | awk -F: '{for(i=1;i<=NF;++i)print $i}' | awk -v OLD_ROOTSYS="${OLD_ROOTSYS}" 'BEGIN{c=0} {if((match($0,OLD_ROOTSYS)==0)||(OLD_ROOTSYS=="")){if(c==1)printf(":"); printf($0); c=1}} END{print ""}'`
if ( "---"${LD_LIBRARY_PATH}"+++" != "---+++" ) then
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}":"
endif
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}${ROOTSYS}"/lib"

#if { ${ROOTSYS_OLD} != "" } then
#  setenv OLD_PATH `printenv | awk -F= '($1=="PATH"){print $2}'`
#  if ( ${OLD_PATH} == != ) then
#    setenv PATH ${ROOTSYS}/bin
#  else
#    setenv PATH ``
#  end
#end

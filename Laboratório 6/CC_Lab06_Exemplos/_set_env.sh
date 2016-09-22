ANTLR_PATH=x/y/z # Coloque aqui o caminho completo do arquivo do ANTLR

export CLASSPATH=".:$ANTLR_PATH/antlr-4.5.2-complete.jar:$CLASSPATH"
alias antlr4="java -jar $ANTLR_PATH/antlr-4.5.2-complete.jar"
alias grun='java org.antlr.v4.gui.TestRig'

FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc Lex_analysis.c -o Lex_analysis
RUN chmod +x Lex_analysis

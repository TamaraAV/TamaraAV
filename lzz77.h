# pragma once

# IfNDef LZ_77_HH_DEF1003
# определить  LZ_77_HH_DEF1003

# include  " define.h "
# включить  " lz77-file.h "

класс  lz77Alg
{
частный:
	lz77Alg ();

	int  strpos ( char * src, int len, char * sub, int sub_len);
	void  add_dict ( char c);
	void  find_match ();

частный:
	буфер символов [BUF_LEN + 1 ], dict [DICT_LEN];
	int match_pos, match_len, несоответствие;
	int dict_pos;

	Lz77Файлы и архивы;
	int in_file, out_file;
общественность:
	lz77Alg ( int InFile, int OutFile, Lz77File & arch);

	void  encode ();
	void  decode ();

};


# endif   // LZ_77_HH_DEF1003

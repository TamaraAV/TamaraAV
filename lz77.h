# pragma once

# IfNDef LZ_77_FILE__HH_DEF1001
# определить  LZ_77_FILE__HH_DEF1001

# включить  < io.h >
# включить  < fcntl.h >
# включить  < string.h >
# включить  < sys / stat.h >

//   Класс для файла Lz77. Декларация
класс  Lz77File
{
	int handle;
	беззнаковый  символ buff_char, маска;
общественность:
	void  assign_read ( int h);
	недействительным  assign_write ( int h);
	void  flush ();

	недействительный  putbit ( BOOL вал);
	bool  getbit ();

	недействительная  putbits ( INT знач, INT N);
	int  getbits ( int n);
};

# endif   // LZ_77_FILE__HH_DEF1001

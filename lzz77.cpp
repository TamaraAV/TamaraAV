# включить  " lz77.h "

# включить  < io.h >
# включить  < fcntl.h >
# включить  < cstring >

// Возвращает позицию с конца src. Вальс [1, лен]

int  lz77Alg :: strpos ( char * src, int len, char * sub, int sub_len)
{
	для ( int i = 0 ; i <= len - sub_len; i ++)
		если ( memcmp (src + i, sub, sub_len) == 0 ) return len - i;
	возврат  0 ;

}


//   Добавляем char c в dict
void  lz77Alg :: add_dict ( символ c)
{
	если (dict_pos == (DICT_LEN - 1 ))
	{
		memcpy (dict, dict + 1 , DICT_LEN - 1 );
		dict [dict_pos - 1 ] = c;
	}
	еще
	{
		dict [dict_pos] = c;
		dict_pos ++;
	}
}

// Находим совпадение в dict
аннулируются  lz77Alg :: find_match ()
{
	match_len = 0 ;
	match_pos = 1 ;
	while (match_len <BUF_LEN)
	{
		_read (in_file, & buffer [match_len], 1 );
		если ( _eof (in_file)) перерыв ;
		int pos1 = strpos (dict, dict_pos, buffer, match_len + 1 );
		если (pos1 == 0 ) перерыв ;
		match_pos = pos1;
		match_len ++;
	}
	unmatched = буфер [match_len];
}

lz77Alg :: lz77Alg ( int InFile, int OutFile, Lz77File & arch): in_file (InFile), out_file (OutFile), архив (arch)
{
	match_pos = match_len = unmatched = dict_pos = 0 ;

}


// ------------------------------------------------ ---------
//
недействительный  lz77Alg :: закодировать ()
{
	пока (! _eof (in_file))
	{
		find_match ();
		архив. путбиты (match_pos, OFFS_LN);
		архив. путбиты (match_len, LEN_LN);
		если (match_len <BUF_LEN)
			архив. путбиты (не совпадают, BYTE_LN);

		для ( int i = 0 ; i <match_len; i ++)
			add_dict (буфер [i]);
		если (match_len <BUF_LEN)
			add_dict (не соответствует);
	}
	архив. путбиты ( 0 , BYTE_LN);
	архив. flush ();
}
// ------------------------------------------------ ---------
//
недействительные  lz77Alg :: декодирование ()
{
	char c;
	int i;
	для (;;)
	{
		match_pos = архив. getbits (OFFS_LN);
		если (match_pos == 0 ) перерыв ;
		match_len = архив. getbits (LEN_LN);
		memcpy (буфер, dict + dict_pos - match_pos, match_len);
		_write (out_file, buffer, match_len);
		for (i = 0 ; i <match_len; i ++)
			add_dict (буфер [i]);
		если (match_len <BUF_LEN)
		{
			c = архив. getbits (BYTE_LN);
			add_dict (c);
			_write (out_file, & c, 1 );
		}
	}
}

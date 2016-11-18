/*
 * LangfordRekursiv.h
 *
 *  Created on: 18.11.2016
 *      Author: hrehmege
 */

#ifndef LANGFORDREKURSIV_H_
#define LANGFORDREKURSIV_H_

class LangfordRekursiv {
public:
	LangfordRekursiv();
	void berechneLoesungen();
	virtual ~LangfordRekursiv();

	int anzSteineProFarbe;
	int anzFarben;
	int anzLoesungen;
};

#endif /* LANGFORDREKURSIV_H_ */

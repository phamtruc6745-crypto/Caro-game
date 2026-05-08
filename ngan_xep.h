#ifndef NGANXEP_H
#define NGANXEP_H

#include "cau_truc_du_lieu.h"
#include <stdbool.h>

typedef struct NodeNuocDi {
    NuocDi nuocDi;
    struct NodeNuocDi* tiepTheo;
} NodeNuocDi;

typedef struct {
    NodeNuocDi* dinh;
} NganXep;

void khoiTaoNganXep(NganXep* nx);
bool themVaoNganXep(NganXep* nx, NuocDi nuoc);
bool layKhoiNganXep(NganXep* nx, NuocDi* nuoc);
bool nganXepRong(NganXep* nx);
void xoaNganXep(NganXep* nx);
void daoNguocNganXep(NganXep* dich, NganXep* nguon);

#endif // NGANXEP_H

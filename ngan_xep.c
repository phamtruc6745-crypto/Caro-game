#include "ngan_xep.h"
#include <stdlib.h>
#include <stdio.h>

void khoiTaoNganXep(NganXep* nx) {
    nx->dinh = NULL;
}

bool themVaoNganXep(NganXep* nx, NuocDi nuoc) {
    NodeNuocDi* nodeMoi = (NodeNuocDi*)malloc(sizeof(NodeNuocDi));
    if (!nodeMoi) return false;
    nodeMoi->nuocDi = nuoc;
    nodeMoi->tiepTheo = nx->dinh;
    nx->dinh = nodeMoi;
    return true;
}

bool layKhoiNganXep(NganXep* nx, NuocDi* nuoc) {
    if (nganXepRong(nx)) return false;
    NodeNuocDi* tam = nx->dinh;
    *nuoc = tam->nuocDi;
    nx->dinh = tam->tiepTheo;
    free(tam);
    return true;
}

bool nganXepRong(NganXep* nx) {
    return nx->dinh == NULL;
}

void xoaNganXep(NganXep* nx) {
    NuocDi nuoc;
    while (!nganXepRong(nx)) {
        layKhoiNganXep(nx, &nuoc);
    }
}

void daoNguocNganXep(NganXep* dich, NganXep* nguon) {
    khoiTaoNganXep(dich);
    NodeNuocDi* hienTai = nguon->dinh;
    while (hienTai != NULL) {
        themVaoNganXep(dich, hienTai->nuocDi);
        hienTai = hienTai->tiepTheo;
    }
}

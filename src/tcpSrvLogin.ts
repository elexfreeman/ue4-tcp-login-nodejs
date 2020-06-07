import * as net from "net";
const moment = require('moment');

import { fGenerateToken } from "./Lib/HashFunc";
import { aSocketClient, db } from "./Module/Sys/db";
import * as AAClasses from '@a-a-game-studio/aa-classes/lib';
import { faUserLogin } from "./Module/User/UserCtrl";
import { fBaseRequest, fRequest, fResponse } from "./Module/Sys/ResponseSys";
import { UserLogin } from "./Module/User/UserR";

/**
 * Текущая дата
 */
const fGetNowDataStr = (): string => moment().format('DD.MM.YYYY HH:mm:ss');

/**
 * Оработчик сервера
 */
const server = net.createServer((socket: net.Socket) => {

    /* генерируем токен клиенту */
    const clientToken = fGenerateToken();
    aSocketClient[clientToken] = true;

    console.log(`[${fGetNowDataStr()}] Client connect ${clientToken}`);


    /* получение данных от клиента */
    socket.on('data', async (data: Buffer) => {
        const errorSys = new AAClasses.Components.ErrorSys();

        console.log(`[${fGetNowDataStr()}] Data from [${clientToken}]: `, data.toString());

        const request: fBaseRequest = fRequest(data, clientToken);

        /* подключаем котролер логина */
        if (request.sRoute == UserLogin.sRequestRoute) {
            await faUserLogin(socket, request, errorSys, db);
        } else {
            /* если маршрут не совпал, отправляет строчку */
            fResponse(socket, {
                sRoute: '',
                ok:true,
                data: {},
                errors: [],
            });
        }

    });

    /* клиент отключися */
    socket.on('end', () => {
        delete aSocketClient[clientToken];
        console.log(`[${fGetNowDataStr()}] Client ${clientToken} disconnect`);
    });

});

/* ошибки сервера */
server.on('error', (err: any) => {
    console.log(`[${fGetNowDataStr()}] Error:`, err);
});


/* запускаем сервер */
server.listen({
    port: 3007, family: 'IPv4', address: '127.0.0.1'
}, () => {
    console.log('opened server on', server.address());
});
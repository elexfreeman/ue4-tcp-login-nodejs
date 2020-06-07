import { conf } from "../Config/Config";

export const db = require('knex')(conf.mysql);


export interface SocketClientI {
    [key: string]: any;
}

/* клиенты */
export const aSocketClient: SocketClientI = {};
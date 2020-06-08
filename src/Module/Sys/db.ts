import { conf } from "../Config/Config";

export const db = require('knex')(conf.mysql); // knex connect

// clients
export interface SocketClientI {
    [key: string]: any;
}

/* clients */
export const aSocketClient: SocketClientI = {};
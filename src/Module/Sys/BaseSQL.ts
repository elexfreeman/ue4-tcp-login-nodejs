
import * as AAClasses from '@a-a-game-studio/aa-classes/lib';

// Системные сервисы
import { KnexSys } from './KnexSys';


/**
 * SQL Запросы
 */
export default class BaseSQL {

    protected db: any;

    protected errorSys: AAClasses.Components.ErrorSys;
    protected knexSys: KnexSys;

    constructor(errorSys: AAClasses.Components.ErrorSys, db: any) {

        this.knexSys = new KnexSys(errorSys);
        this.errorSys = errorSys;
        this.db = db;
    }

}

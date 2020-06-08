
import * as AAClasses from '@a-a-game-studio/aa-classes/lib';

// System services
import { KnexSys } from './KnexSys';


/**
 * SQL
 */
export default class BaseSQL {

    protected db: any;

    protected errorSys: AAClasses.Components.ErrorSys;
    protected knexSys: KnexSys;

    constructor(errorSys: AAClasses.Components.ErrorSys, db: any) {

        this.knexSys = new KnexSys(errorSys);
        this.errorSys = errorSys;
        this.db = db; // knex connect
    }

}

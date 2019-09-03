(*!------------------------------------------------------------
 * [[APP_NAME]] ([[APP_URL]])
 *
 * @link      [[APP_REPOSITORY_URL]]
 * @copyright Copyright (c) [[COPYRIGHT_YEAR]] [[COPYRIGHT_HOLDER]]
 * @license   [[LICENSE_URL]] ([[LICENSE]])
 *------------------------------------------------------------- *)

 {-----------------------------------------------
   register middleware list for global routes that
   need to be use single instance
 ------------------------------------------------}
container.add('appMiddlewares', TMiddlewareCollectionAwareFactory.create());

 {-----------------------------------------------
   register middleware list for each routes that
   does nothing,
   need to be use factory so each route will have
   different middleware list
   Replace with TMiddlewareCollectionAwareFactory to support middleware
   or replace with your own implementation if required
 ------------------------------------------------}
container.factory('routeMiddlewares', TNullMiddlewareCollectionAwareFactory.create());

container.add(
    'cors',
    (TCorsMiddlewareFactory.create())
        .allowedOriginsPatterns(['http\:\/\/localhost\:[0-9]{1,5}'])
        .allowedMethods(['GET', 'POST', 'OPTIONS'])
        .allowedHeaders(['X-My-Custom-Header'])
);

appMiddlewares := container.get('appMiddlewares') as IMiddlewareCollectionAware;
appMiddlewares.addBefore(container.get('cors') as IMiddleware);

container.add(
    GuidToString(IDispatcher),
    TDispatcherFactory.create(
        appMiddlewares,
        container.get(GuidToString(IRouteMatcher)) as IRouteMatcher,
        TRequestResponseFactory.create()
    )
);

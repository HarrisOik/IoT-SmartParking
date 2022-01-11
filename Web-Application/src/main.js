import { createApp, h } from 'vue';
import { Home, Register, Spots } from './pages';

const NotFoundComponent = { template: '<p>Page not found</p>' };

const routes = {
  '/': Home,
  '/register': Register,
  '/spots': Spots
};

const SimpleRouter = {
  data: () => ({
    currentRoute: window.location.pathname
  }),

  computed: {
    CurrentComponent() {
      return routes[this.currentRoute] || NotFoundComponent;
    }
  },

  render() {
    return h(this.CurrentComponent);
  }
};

createApp(SimpleRouter).mount('#app');

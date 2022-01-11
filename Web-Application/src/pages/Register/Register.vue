<template>
  <Header />
  <Content />
  <Footer />
</template>
<script>
import Content from "./components/Content.vue";
import Header from "../../components/Header.vue";
import Footer from "../../components/Footer.vue";

export default {
  name: "Register",
  components: {
    Content,
    Header,
    Footer,
  },
};
</script>

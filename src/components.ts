/**
 * MDX globals registry — components available inside MDX without `import`.
 * Wired via `<Content components={components} />` in `[...slug].astro`.
 * Add new components here as you build (or install) them.
 */

import { Aside } from "./components/ui/aside";
import Render from "./components/Render.astro";
import PrintButton from "./components/PrintButton.astro";
import Preview from "./components/Preview.astro";
import Notebook from "./components/Notebook.astro";
import Explain from "./components/Explain.astro";
import Math from "./components/Math.astro";
import LanguagePicker from "./components/LanguagePicker.astro";
import { Card } from "./components/ui/card";
import { CardGrid } from "./components/ui/card-grid";
import { PackageManagers } from "./components/ui/package-managers";
import { Step, Steps } from "./components/ui/steps";
import { Tabs, TabItem } from "./components/ui/tabs";

export const components = {
  Aside,
  Card,
  Explain,
  LanguagePicker,
  Math,
  CardGrid,
  PackageManagers,
  Preview,
  Notebook,
  PrintButton,
  Render,
  Step,
  Steps,
  TabItem,
  Tabs,
};
